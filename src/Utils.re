let fetchAndDecode = (url, decodeFn) =>
  Js.Promise.(
    Fetch.fetch(url)
    |> then_(Fetch.Response.json)
    |> then_(json => decodeFn(json) |> Belt.Result.getExn |> resolve)
  );
