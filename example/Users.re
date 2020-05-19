let users = [|"John", "Paul", "George", "Ringo"|];

[@react.component]
let make = () => {
  <div>
    <h1> {React.string("choose who you want to say hello to :")} </h1>
    {users
     ->Belt.Array.map(name =>
         <Link
           key=name route={Routes.sprintf(Targets.greeting(), name, "Hello")}>
           <li> {React.string(name)} </li>
         </Link>
       )
     ->React.array}
  </div>;
};