open Types;
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
      Decoders.decodePhotos,
    );
};

type action =
  | FetchPhotos
  | PhotosLoading(bool)
  | SetPhotos(list(photo))
  | SetModalOpen(int)
  | SetModalClosed
  | SetItemToLocalStorage(string, string);

type state = {
  photos: list(photo),
  modalOpen: bool,
  modalId: int,
  loading: bool,
};

[@react.component]
let make = _ => {
  let (state, send) =
    ReactUpdate.useReducer(
      {photos: [], modalOpen: false, modalId: 0, loading: false},
      (action, state) =>
      switch (action) {
      | FetchPhotos =>
        UpdateWithSideEffects(
          state,
          ({send}) => {
            ignore(send(PhotosLoading(true)));
            ignore(
              API.getPhotos()
              |> Js.Promise.then_(photos => {
                   let filteredPhotos =
                     List.filter(photo => photo.id < 26, photos);
                   send(SetPhotos(filteredPhotos)) |> Js.Promise.resolve;
                 }),
            );
            ignore(send(PhotosLoading(false)));
            Some(() => ());
          },
        )
      | PhotosLoading(loading) => Update({...state, loading})
      | SetPhotos(photos) => Update({...state, photos})
      | SetModalOpen(id) => Update({...state, modalOpen: true, modalId: id})
      | SetModalClosed => Update({...state, modalOpen: false})
      | SetItemToLocalStorage(string, id) =>
        UpdateWithSideEffects(
          state,
          ({send}) => {
            Dom.Storage.(localStorage |> setItem("image" ++ id, string));
            send(SetModalClosed);
            Some(() => ());
          },
        )
      }
    );
  React.useEffect0(() => {
    send(FetchPhotos);
    None;
  });
  state.loading
    ? <h1> {React.string("...Loading")} </h1>
    : <div className=Styles.container>
        <div className=Styles.photoContainer>
          {state.modalOpen
             ? <PhotoModal
                 photo={List.hd(
                   List.filter(
                     photo => photo.id == state.modalId,
                     state.photos,
                   ),
                 )}
                 setModalClosed={_ => send(SetModalClosed)}
                 onInputSubmit={(value, id) =>
                   send(SetItemToLocalStorage(value, id))
                 }
               />
             : React.null}
          {React.array(
             Array.of_list(
               List.map(
                 item =>
                   <PhotoItem
                     url={item.url}
                     id={item.id}
                     title={item.title}
                     thumbnailUrl={item.thumbnailUrl}
                     setModalOpen={() => send(SetModalOpen(item.id))}
                   />,
                 state.photos,
               ),
             ),
           )}
        </div>
      </div>;
};