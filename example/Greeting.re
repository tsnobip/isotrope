[@react.component]
let make = (~name: string, ~greeting: string) =>
  React.string({j|$greeting $name!|j});