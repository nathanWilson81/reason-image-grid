// Generated by BUCKLESCRIPT, PLEASE EDIT WITH CARE
'use strict';

var Css = require("bs-css/src/Css.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");

var modalMask = Css.style(/* :: */[
      Css.position(/* absolute */-1013592457),
      /* :: */[
        Css.height(/* `percent */[
              -119887163,
              100.0
            ]),
        /* :: */[
          Css.width(/* `percent */[
                -119887163,
                100.0
              ]),
          /* :: */[
            Css.top(/* `pt */[
                  25092,
                  0
                ]),
            /* :: */[
              Css.left(/* `pt */[
                    25092,
                    0
                  ]),
              /* :: */[
                Css.justifyContent(/* center */98248149),
                /* :: */[
                  Css.alignItems(/* center */98248149),
                  /* :: */[
                    Css.display(/* flex */-1010954439),
                    /* :: */[
                      Css.backgroundColor(Css.rgba(15, 17, 20, 0.5)),
                      /* [] */0
                    ]
                  ]
                ]
              ]
            ]
          ]
        ]
      ]
    ]);

var modalContent = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* :: */[
        Css.justifyContent(/* center */98248149),
        /* :: */[
          Css.alignItems(/* center */98248149),
          /* :: */[
            Css.flexDirection(/* column */-963948842),
            /* [] */0
          ]
        ]
      ]
    ]);

var buttonContainer = Css.style(/* :: */[
      Css.display(/* flex */-1010954439),
      /* [] */0
    ]);

var Styles = {
  modalMask: modalMask,
  modalContent: modalContent,
  buttonContainer: buttonContainer
};

function PhotoModal(Props) {
  var photo = Props.photo;
  var photos = Props.photos;
  var setModalClosed = Props.setModalClosed;
  var onInputSubmit = Props.onInputSubmit;
  var match = React.useState((function () {
          var storageItem = localStorage.getItem("image" + String(photo.id));
          if (storageItem !== null) {
            return storageItem;
          } else {
            return "";
          }
        }));
  var setInputValue = match[1];
  var inputValue = match[0];
  return React.createElement("div", {
              className: modalMask,
              onClick: (function (param) {
                  return Curry._1(setModalClosed, photos);
                })
            }, React.createElement("div", {
                  onClick: (function (e) {
                      e.stopPropagation();
                      return /* () */0;
                    })
                }, React.createElement("h3", undefined, photo.title), React.createElement("img", {
                      src: photo.url
                    }), React.createElement("div", {
                      className: buttonContainer
                    }, React.createElement("input", {
                          value: inputValue,
                          onChange: (function (e) {
                              e.stopPropagation();
                              return Curry._1(setInputValue, e.target.value);
                            })
                        }), React.createElement("button", {
                          onClick: (function (param) {
                              return Curry._2(onInputSubmit, inputValue, String(photo.id));
                            })
                        }, "Submit"), React.createElement("button", {
                          onClick: (function (param) {
                              return Curry._1(setModalClosed, photos);
                            })
                        }, "Close"))));
}

var make = PhotoModal;

exports.Styles = Styles;
exports.make = make;
/* modalMask Not a pure module */
