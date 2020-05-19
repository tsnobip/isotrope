open! Routes;
let root = () => empty;
let users = () => s("users") /? nil;
let greeting = () => s("greeting") / str / str /? nil;