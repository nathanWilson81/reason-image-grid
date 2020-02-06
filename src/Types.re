[@decco]
type photo = {
  albumId: int,
  id: int,
  title: string,
  url: string,
  thumbnailUrl: string,
};

[@decco]
type photos = list(photo);
