open CallbagBasics;

open CallbagStore;

open BsDeclaredom;
open Html;
let css_module = Css.Module.make(Css.inline(~margin_right=`em(1.), ()));

let stylesheet = Css_Stylesheet.make(`utf_8, [Css_Stylesheet.css_module(css_module)]);

type state = {counter: int};

type action =
  | Increment
  | Decrement;

let {dispatch, store, get_state} =
  {counter: 0}
  |> make @@
  (
    ({counter}, action) =>
      switch action {
      | Increment => {counter: counter + 1}
      | Decrement => {counter: counter - 1}
      }
  );

let counter =
  store
  |> map(({counter}) => span(~css_module, [|text @@ string_of_int(counter)|]))
  |> CallbagElement.make(_);


let example =
  div([|
    counter,
    button(~on_click=(_) => dispatch(Increment), [|text("Increment")|]),
    button(~on_click=(_) => dispatch(Decrement), [|text("Decrement")|])
  |]);

{
  let body =
    Webapi.Dom.(
      document
      |> Document.asHtmlDocument
      |> Js.Option.andThen([@bs] ((e) => HtmlDocument.body(e)))
      |> Js.Option.getExn
    );
  let style = {
    open Webapi.Dom;
    let style = document |> Document.createElement("style");
    Element.setInnerHTML(style, Css.Stylesheet.show(stylesheet));
    style;
  };
  Webapi.Dom.Element.appendChild(style, body);
  Webapi.Dom.Element.appendChild(Html.Node.to_node(example), body);
};
