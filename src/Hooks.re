/*
 * Heavily inspired by ReasonReact Router
 */

[@bs.get] external location: Dom.window => Dom.location = "location";
[@bs.get] external pathname: Dom.location => string = "pathname";
[@bs.send]
/* actually the cb is Dom.event => unit, but let's restrict the access for now */
external addEventListener: (Dom.window, string, (. unit) => unit) => unit =
  "addEventListener";
[@bs.send]
external removeEventListener: (Dom.window, string, (. unit) => unit) => unit =
  "removeEventListener";

[@bs.send]
external dispatchEvent: (Dom.window, Dom.event) => unit = "dispatchEvent";
let url = () =>
  switch ([%external window]) {
  | None => ""
  | Some((window: Dom.window)) => window->location->pathname
  };
let dangerouslyGetInitialUrl = url;
type watcherID = (. unit) => unit;
let watchUrl = callback =>
  switch ([%external window]) {
  | None => ((.) => ())
  | Some((window: Dom.window)) =>
    let watcherID = ((.) => callback(. url()));
    addEventListener(window, "popstate", watcherID);
    watcherID;
  };
let unwatchUrl = watcherID =>
  switch ([%external window]) {
  | None => ()
  | Some((window: Dom.window)) =>
    removeEventListener(window, "popstate", watcherID)
  };

let useUrl = (~serverUrl=?, ()) => {
  let (url, setUrl) =
    React.useState(() =>
      switch (serverUrl) {
      | Some(url) => url
      | None => dangerouslyGetInitialUrl()
      }
    );

  React.useEffect0(() => {
    let watcherId = watchUrl((. url) => setUrl(_ => url));

    /**
      * check for updates that may have occured between
      * the initial state and the subscribe above
      */
    let newUrl = dangerouslyGetInitialUrl();
    if (newUrl !== url) {
      setUrl(_ => newUrl);
    };

    Some(() => unwatchUrl(watcherId));
  });

  url;
};