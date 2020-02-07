module Promise = {
  include Promise;
  let let_ = Promise.flatMap;
};

type response;
[@bs.val] external fetch: string => Promise.t(response) = "fetch";
[@bs.send] external toJson: response => Promise.t(Js.Json.t) = "json";

let fetchAndDecode = (url, decodeFn) => {
  let%Promise result = fetch(url);
  let%Promise jsonResult = toJson(result);
  decodeFn(jsonResult) |> Belt.Result.getExn |> Promise.resolved;
};
