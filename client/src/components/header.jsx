// Imports
import React, { Component } from "react";
import { Link } from "react-router-dom";

class Header extends Component {
  render() {
    return (
      <React.Fragment>
        <Link
          to="/"
          className="brand-logo"
        >
          RGB Controller
        </Link>
      </React.Fragment>
    );
  }
}

export default Header;
