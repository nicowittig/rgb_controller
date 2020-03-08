from threading import Thread

import neopixel
from flask import Flask, jsonify, request
from input import Input_Analog, Input_Temperature

#from flask_cors import CORS, cross_origin

app = Flask(__name__)
#cors = CORS(app)
#cors = CORS(app, resources={r"/api/*": {"origins": "*"}})
#app.config['CORS_HEADERS'] = 'Content-Type'

class Controller(Thread):
    def __init__(self, config):
        super().__init__()

        self.__active = True

        self.__api_host = config.host
        self.__api_port = config.port
        self.__api_debug = config.debug

        self.__mode_switch = config.mode_switch
        self.__light_elements = config.light_elements
        self.__inputs = config.inputs
        self.__effects = []

        num_pixels = 0
        for le in self.__light_elements:
            num_pixels += le.num_pixels
        self.__neoPixels = neopixel.NeoPixel(config.board_pin, num_pixels)

        self.__mode = config.default_mode
        self.switch_mode(self.__mode)

        return None

    def run(self):
        t_refresh_inputs = Thread(target=self.refresh_inputs)
        t_refresh_temperature_inputs = Thread(target=self.refresh_temperture_inputs)
        t_refresh_inputs.start()
        t_refresh_temperature_inputs.start()

        app.run(host=self.__api_host, port=self.__api_port, debug=self.__api_debug)

        while self.__active:
            self.run_effects()
            self.show_all()

        return None

    def stop(self):
        self.__active = False
        return None

    @app.route('/api/v1/mode', methods=['POST'])
    #@cross_origin()
    def api_switch_mode(self):
        mode = request.json["mode"] 

        if mode == "r":
            self.adjust_all_analog_inputs()
        else:
            self.__mode = mode
            self.__effects = self.__mode_switch(mode)
            self.init_effects()

        return jsonify({'mode': mode})

    @app.route('/api/v1/input', methods=['POST'])
    #@cross_origin()
    def external_tap(self):
        input = request.json["input"] 
        self.__inputs[input].external_tap()
        return jsonify({'input': self.__inputs[input]})

    def adjust_all_analog_inputs(self):
        for i in self.__inputs:
            if isinstance(i, Input_Analog):
                i.adjust_trigger_value()
        return None

    def refresh_inputs(self):
        while self.__active:
            for i in self.__inputs:
                if not isinstance(i, Input_Temperature):
                    i.refresh()
        return None

    def refresh_temperture_inputs(self):
        while self.__active:
            for i in self.__inputs:
                if isinstance(i, Input_Temperature):
                    i.refresh()
        return None

    def init_effects(self):
        for e in self.__effects:
            e.init()
        return None

    def run_effects(self):
        for e in self.__effects:
            e.run()
        return None

    def show_all(self):
        pixels = []
        for le in self.__light_elements:
            pixels += le.show()
        self.__neoPixels[::] = pixels
        return None
