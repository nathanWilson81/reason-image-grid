open Types;
open Jest;
open JestDom;
open Expect;
open ReactTestingLibrary;

describe("PhotoItem", () => {
  let photo = {
    albumId: 1,
    id: 1,
    title: "This is the title",
    url: "foo1",
    thumbnailUrl: "foo2",
  };
  let photos = [photo];
  let setModalOpen = [%raw {|jest.fn()|}];
  test("renders the item", () =>
    <PhotoItem photo photos setModalOpen />
    |> render
    |> container
    |> expect
    |> toMatchSnapshot
  );
  test("sets the src on the image", () =>
    <PhotoItem photo photos setModalOpen />
    |> render
    |> getByAltText("")
    |> expect
    |> toHaveAttribute("src", ~value="foo1")
  );
});
