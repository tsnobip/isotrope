/*
 * Heavily inspired from Alexey Fedoseev's MinimaHQ /safe-routing-blog-app-example
 */

/**
 * The Link component allows you to navigate to the routes defined in your application.
 */
[@react.component]
let make = (~route, ~children) => {
  <a
    href=route
    onClick={event =>
      if (!event->ReactEvent.Mouse.defaultPrevented
          && event->ReactEvent.Mouse.button == 0
          && !event->ReactEvent.Mouse.altKey
          && !event->ReactEvent.Mouse.ctrlKey
          && !event->ReactEvent.Mouse.metaKey
          && !event->ReactEvent.Mouse.shiftKey) {
        event->ReactEvent.Mouse.preventDefault;
        route->ReasonReactRouter.push;
      }
    }>
    children
  </a>;
};