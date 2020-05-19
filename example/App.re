module MyRoutes = {
  open Routes;
  let rootRoute = () => Targets.root() @--> <Users />;
  let usersRoute = () => Targets.users() @--> <Users />;
  let greetingRoute = () =>
    Targets.greeting() @--> ((name, greeting) => <Greeting name greeting />);

  let routes = one_of([rootRoute(), usersRoute(), greetingRoute()]);
};

[@react.component]
let make = () => {
  let target = Hooks.useUrl();
  switch (Routes.match'(MyRoutes.routes, ~target)) {
  | Some(element) => element
  | None => <NotFound />
  };
};