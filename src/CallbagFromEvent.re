[@bs.module "callbag-from-event"]
external from_event: (Dom.element, string) => Callbag.t(Dom.event) =
  "default";
