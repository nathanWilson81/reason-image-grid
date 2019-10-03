// Generated by BUCKLESCRIPT VERSION 5.0.6, PLEASE EDIT WITH CARE
'use strict';

var Jest = require("@glennsl/bs-jest/src/jest.js");
var React = require("react");
var JestDom = require("bs-jest-dom/src/JestDom.bs.js");
var ReactTestingLibrary = require("bs-react-testing-library/src/ReactTestingLibrary.bs.js");
var PhotoItem$ReactHooksTemplate = require("../src/PhotoItem.bs.js");

Jest.describe("PhotoItem", (function (param) {
        var photo = /* record */[
          /* albumId */1,
          /* id */1,
          /* title */"This is the title",
          /* url */"foo1",
          /* thumbnailUrl */"foo2"
        ];
        var photos = /* :: */[
          photo,
          /* [] */0
        ];
        var setModalOpen = (jest.fn());
        Jest.test("renders the item", (function (param) {
                var eta = React.createElement(PhotoItem$ReactHooksTemplate.make, {
                      photo: photo,
                      photos: photos,
                      setModalOpen: setModalOpen
                    });
                return Jest.Expect[/* toMatchSnapshot */16](Jest.Expect[/* expect */0](ReactTestingLibrary.render(undefined, undefined, eta).container));
              }));
        return Jest.test("sets the src on the image", (function (param) {
                      var eta = React.createElement(PhotoItem$ReactHooksTemplate.make, {
                            photo: photo,
                            photos: photos,
                            setModalOpen: setModalOpen
                          });
                      return JestDom.toHaveAttribute("src", "foo1", Jest.Expect[/* expect */0](ReactTestingLibrary.getByAltText("", ReactTestingLibrary.render(undefined, undefined, eta))));
                    }));
      }));

/*  Not a pure module */
