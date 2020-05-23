# Isotrope

Isotrope is a very basic experiment of a safe bi-directional router in ReasonReact thanks to [@anuragsoni/routes](https://github.com/anuragsoni/routes) awesome routing lib. 

Define your routes once and use them both ways.

## Install
```
yarn add @tsnobip/isotrope @anuragsoni/routes
```

And add `@tsnobip/isotrope` and `@anuragsoni/routes` to the `bs-dependencies` of `bsconfig.json`.

## Usage

You can refer to the [example](https://github.com/tsnobip/isotrope/tree/master/example) folder for a working example.

Start with defining your route patterns (more info in [@anuragsoni/routes docs](https://github.com/anuragsoni/routes)), for example in `Targets.re`:
```reason
open! Routes;
let root = () => empty;
let users = () => s("users") /? nil;
let greeting = () => s("greeting") / str / str /? nil;
```

Then create the router by connecting a function to each route pattern: 
```reason
module MyRoutes = {
  open Routes;
  let rootRoute = () => Targets.root() @--> <Users />;
  let usersRoute = () => Targets.users() @--> <Users />;
  let greetingRoute = () =>
    Targets.greeting() @--> ((name, greeting) => <Greeting name greeting />);

  let routes = one_of([rootRoute(), usersRoute(), greetingRoute()]);
};

```

You can then use your router this way:
```reason
let target = Isotrope.Hooks.useUrl();
switch (Routes.match'(MyRoutes.routes, ~target)) {
| Some(element) => element
| None => <NotFound />
};
```

You can also safely generate a url like this:
```reason
open Isotrope;
<Link route={Routes.sprintf(Targets.greeting(), "World", "Hello")}>
  {React.string("World")}
</Link>
```

## Remaining tasks

- [ ] add support for hashes and query parameters
- [ ] better integration of @anurasgoni/Routes 

