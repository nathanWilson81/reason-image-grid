open Types;
module Styles = {
  open Css;
  let modalMask =
    style([
      position(`absolute),
      height(`percent(100.0)),
      width(`percent(100.0)),
      top(`pt(0)),
      left(`pt(0)),
      justifyContent(`center),
      alignItems(`center),
      display(`flex),
      backgroundColor(rgba(15, 17, 20, 0.5)),
    ]);

  let modalContent =
    style([
      display(`flex),
      justifyContent(`center),
      alignItems(`center),
      flexDirection(`column),
    ]);

  let buttonContainer = style([display(`flex)]);
};

[@react.component]
let make = (~photo, ~setModalClosed, ~onInputSubmit) => {
  let (inputValue, setInputValue) =
    React.useState(() => {
      let storageItem =
        Dom.Storage.(
          localStorage |> getItem("image" ++ string_of_int(photo.id))
        );
      switch (storageItem) {
      | Some(value) => value
      | None => ""
      };
    });
  <div className=Styles.modalMask onClick={_ => setModalClosed(inputValue)}>
    <div onClick={e => ReactEvent.Mouse.stopPropagation(e)}>
      <h3> {React.string(photo.title)} </h3>
      <img src={photo.url} />
      <div className=Styles.buttonContainer>
        <input
          value=inputValue
          onChange={e => {
            ReactEvent.Form.stopPropagation(e);
            setInputValue(ReactEvent.Form.target(e)##value);
          }}
        />
        <button
          onClick={_ => onInputSubmit(inputValue, string_of_int(photo.id))}>
          {React.string("Submit and close")}
        </button>
        <button onClick={_ => setModalClosed(inputValue)}>
          {React.string("Close")}
        </button>
      </div>
    </div>
  </div>;
};