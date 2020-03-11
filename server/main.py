import sys
from argparse import ArgumentParser

import config as config
from color import Color
from controller import Controller
from flask import Flask, Response, jsonify, request

sys.path.append("/home/pi/.local/lib/python3.7/site-packages")
from flask_cors import CORS, cross_origin

app = Flask(__name__)
cors = CORS(app)

controller = Controller(config)

@app.route('/api/v1/init', methods=['GET'])
def api_init():
    init_json = config.init_json
    init_json["general"]["brightness"] = controller.get_brightness()
    return jsonify(init_json)

@app.route('/api/v1/general', methods=['POST'])
def api_general():
    key = request.json["key"]
    if key == "on":
        controller.start()
    elif key == "off":
        controller.stop()
    elif key == "calibrate":
        controller.adjust_all_analog_inputs()
    elif key == "input-all":
        for i in range(len(config.inputs)):
            controller.external_tap(i)
    elif key == "input-reset-all":
        controller.reset_all_inputs()
    else:
        print("key not found: " + key)
        None
    return Response(status=200)

@app.route('/api/v1/mode', methods=['POST'])
def mode():
    key = request.json["key"]
    controller.switch_mode(key)
    return Response(status=200)

@app.route('/api/v1/input', methods=['POST'])
def input():
    key = request.json["key"]
    controller.external_tap(key)
    return Response(status=200)

@app.route('/api/v1/brightness', methods=['POST'])
def brightness():
    value = request.json["value"]
    controller.set_brightness(value)
    return Response(status=200)

if __name__ == '__main__':
    controller.start()
    app.run(host=config.api_host, port=config.api_port, debug=config.api_debug)
