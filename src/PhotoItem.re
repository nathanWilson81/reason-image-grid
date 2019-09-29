module Styles = {
  open Css;
  let photoItem = style([height(px(150)), width(px(150))]);
  let container = style([
    marginLeft(`rem(2.0)),
    marginBottom(`rem(2.0))
  ]);
};

[@react.component]
let make = (~id, ~title, ~thumbnailUrl, ~url, ~setModalOpen) =>
  <div className={Styles.container} onClick={_ => setModalOpen()}>
    <img className={Styles.photoItem} src=url />
  </div>