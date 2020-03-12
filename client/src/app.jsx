// Imports
import React, { Component } from 'react';
import { BrowserRouter, Route, Switch } from 'react-router-dom';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';
import Slider from 'react-input-slider';

import Header from './components/header.jsx';
import Footer from './components/footer.jsx';

import './styles/app.css';
import 'bootstrap/dist/css/bootstrap.css';

const axios = require('axios');

export default class App extends Component {
  constructor(props) {
    super(props);

    // page settings
    this.state = {
      apiUrl: "http://192.168.178.150:2001/api/v1",
      switches: [],
      generals: [],
      modes: [],
      inputs: [],
      brightness: 100,
      connected: false
    };

    axios.defaults.baseURL = this.state.apiUrl;

    this.init = this.init.bind(this);
    this.onButtonClick = this.onButtonClick.bind(this);
    this.onChangeBrightness = this.onChangeBrightness.bind(this);
    this.getButtonItems = this.getButtonItems.bind(this);

    this.init();
  }

  init() {
    axios.get('init', {})
    .then(response => {
      setTimeout(() => {
        var modes = response.data.modes
        modes.elements.sort((a, b) => a.id - b.id)
        console.log(response.data.general.brightness * 100)

        this.setState({
          switches: response.data.switches,
          generals: response.data.general,
          modes: modes,
          inputs: response.data.inputs,
          brightness: response.data.general.brightness * 100,
          connected: true,
          showApiError: false
        });
      }, 0);
    })
    .catch(error => {
      this.setState({ showApiError: true });
      console.log(error);
    });
  }

  onButtonClick(api, key) {
    axios.post(api, {key: key})
    .then(response => {
      setTimeout(() => {
        this.setState({ showApiError: false });
      }, 0);
    })
    .catch(error => {
      this.setState({ showApiError: true });
      console.log(error);
    });
  }

  onChangeBrightness() {
    axios.post('brightness', {value: this.state.brightness/100})
    .then(response => {
      setTimeout(() => {
        this.setState({ showApiError: false });
      }, 0);
    })
    .catch(error => {
      this.setState({ showApiError: true });
      console.log(error);
    });
  }

  getButtonItems(items) {
    var index = 0
    if (items.elements) {
      return(items.elements.map(e => (
          <Button key={index++} className={"btn-" + e.key} variant="primary" type="button" onClick={() => this.onButtonClick(items.api, e.key)}>
            {e.name}
          </Button>
      )));
    }

    return null
  }

  render() {
    return (
      <BrowserRouter>
        <React.Fragment>
          <nav>
            <Header />
          </nav>
          <div className="body">
            {this.state.connected ? 
              <React.Fragment>
                <Form>
                  <div className="btn-row btn-switches">{this.getButtonItems(this.state.switches)}</div>
                  <div className="brightness-label dark-mode">
                    <p>Brightness: {Math.round(this.state.brightness)}%</p>
                  </div>

                  <Slider
                    axis="x"
                    x={this.state.brightness}
                    xmin={0}
                    xmax={100}
                    xstep={5}
                    onChange={({x}) => this.setState({ brightness: x })}
                    onDragEnd={this.onChangeBrightness}
                    styles={{
                      track: {
                        backgroundColor: '#555456'
                      },
                      active: {
                        backgroundColor: '#aaa'
                      },
                      thumb: {
                        width: 30,
                        height: 30
                      },
                      disabled: {
                        opacity: 0.5
                      }
                    }}
                  />

                  <div className="btn-row btn-generals">{this.getButtonItems(this.state.generals)}</div>
                  <div className="btn-row btn-modes">{this.getButtonItems(this.state.modes)}</div>
                  <div className="btn-row btn-inputs">{this.getButtonItems(this.state.inputs)}</div>
                  {this.state.show_api_Error && (
                    <Form.Label className="error">Api Error!</Form.Label>
                  )}
                </Form>
              </React.Fragment>
            :
              <div className="brightness-label dark-mode">
                <p>Not connected!</p>
              </div>
            }

          </div>
          <footer>
            <Footer />
          </footer>
        </React.Fragment>
      </BrowserRouter>
    );
  }
}