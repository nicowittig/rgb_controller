// Imports
import React, { Component } from 'react';
import { BrowserRouter, Route, Switch } from 'react-router-dom';
import Button from 'react-bootstrap/Button';
import Form from 'react-bootstrap/Form';

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
      modes: [
        { key: 0, name: "Off" },
        { key: 1, name: "Static Color" },
        { key: 2, name: "Interactive Spin" },
        { key: 3, name: "Meteor" },
        { key: 4, name: "Thermometer" },
        { key: "r", name: "Calibrate Sensors" }

      ]
    }

    axios.defaults.baseURL = this.state.apiUrl;

    this.switchMode = this.switchMode.bind(this);
  }

  switchMode(mode) {
    const reqObj = {
      mode: mode
    };

    axios.post('mode', reqObj)
    .then(response => {
      setTimeout(() => {
        console.log(response)
        this.setState({ showApiError: false });
      }, 0);
    })
    .catch(error => {
      this.setState({ showApiError: true });
      console.log(error);
    });
  }

  getModeButtonItems() {
    var index = 0
    return(this.state.modes.map(m => (
      <div key={index++}>
        <Button className="btn-submit" variant="primary" type="button" onClick={() => this.switchMode(m.key)}>
          {m.name}
        </Button>
      </div>
    )));
  }

  render() {
    return (
      <BrowserRouter>
        <React.Fragment>
          <nav>
            <Header />
          </nav>
          <div className="body">

            <React.Fragment>
              <Form>
                {this.getModeButtonItems()}
                {this.state.show_api_Error && (
                  <Form.Label className="error">Api Error!</Form.Label>
                )}
              </Form>
            </React.Fragment>

          </div>
          <footer>
            <Footer />
          </footer>
        </React.Fragment>
      </BrowserRouter>
    );
  }
}