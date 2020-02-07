open Types;
open Utils;

module Styles = {
  open Css;
  let container =
    style([
      height(`percent(100.0)),
      width(`percent(100.0)),
      display(`flex),
      justifyContent(`center),
    ]);
  let photoContainer =
    style([display(`flex), flexWrap(`wrap), maxWidth(`px(1000))]);
};

module API = {
  let getPhotos = () =>
    Utils.fetchAndDecode(
      "https://jsonplaceholder.typicode.com/photos",
      Types.photos_decode,
    );
};

type visualState =
  | Loading
  | Loaded(list(photo))
  | Error(string)
  | Modal(photo, list(photo));

type action =
  | FetchPhotos
  | SetModalOpen(photo, list(photo))
  | SetModalClosed(list(photo))
  | SetVisualState(visualState)
  | SetItemToLocalStorage(string, string);

type state = {visualState};

[@react.component]
let make = _ => {
  let (state, send) =
    ReactUpdate.useReducer({visualState: Loading}, (action, state) =>
      switch (action) {
      | SetVisualState(visualState) => Update({visualState: visualState})
      | FetchPhotos =>
        UpdateWithSideEffects(
          state,
          ({send}) => {
            ignore(
              {
                let%Promise photos = API.getPhotos();
                let filteredPhotos =
                  List.filter(photo => photo.id < 26, photos);
                Promise.resolved(
                  send(SetVisualState(Loaded(filteredPhotos))),
                );
              },
            );
            None;
          },
        )
      | SetModalOpen(photo, photos) =>
        Update({visualState: Modal(photo, photos)})
      | SetModalClosed(photos) => Update({visualState: Loaded(photos)})
      | SetItemToLocalStorage(string, id) =>
        UpdateWithSideEffects(
          state,
          _ => {
            Dom.Storage.(localStorage |> setItem("image" ++ id, string));
            None;
          },
        )
      }
    );
  React.useEffect0(() => {
    send(FetchPhotos);
    None;
  });
  switch (state.visualState) {
  | Loading => <h1> {React.string("...Loading")} </h1>
  | Modal(photo, photos) =>
    <PhotoModal
      photo
      photos
      onInputSubmit={(value, id) => send(SetItemToLocalStorage(value, id))}
      setModalClosed={photos => send(SetModalClosed(photos))}
    />
  | Error(message) => <h1> {React.string("Uh oh: " ++ message)} </h1>
  | Loaded(photos) =>
    <div className=Styles.container>
      <div className=Styles.photoContainer>
        {React.array(
           Array.of_list(
             photos
             |> List.map(item =>
                  <PhotoItem
                    key={string_of_int(item.id)}
                    photo=item
                    photos
                    setModalOpen={(photo, photos) =>
                      send(SetModalOpen(photo, photos))
                    }
                  />
                ),
           ),
         )}
      </div>
    </div>
  };
};
