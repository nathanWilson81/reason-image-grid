open Types;
open Jest;
open JestDom;
open Expect;
open ReactTestingLibrary;

describe("PhotoModal", () => {
  let photo = {
    albumId: 1,
    id: 1,
    title: "This is the title",
    url: "foo1",
    thumbnailUrl: "foo2",
  };
  let photos = [photo];
  let onInputSubmit = [%raw {|jest.fn()|}];
  let setModalClosed = [%raw {|jest.fn()|}];
  test("renders the modal", () =>
    <PhotoModal photo photos onInputSubmit setModalClosed />
    |> render
    |> container
    |> expect
    |> toMatchSnapshot
  );
  test("title shows", () =>
    <PhotoModal photo photos onInputSubmit setModalClosed />
    |> render
    |> getByText(~matcher=`Str("This is the title"))
    |> expect
    |> toBeInTheDocument
  );
});
