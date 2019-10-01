open Types;
open Json.Decode;
let decodePhotos =
  list(json =>
    {
      albumId: field("albumId", int, json),
      id: field("id", int, json),
      title: field("title", string, json),
      url: field("url", string, json),
      thumbnailUrl: field("thumbnailUrl", string, json),
    }
  );
