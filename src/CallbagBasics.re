type observable('a, 'b) = Js.t({.. subscribe: ('a => unit) => unit} as 'b);

module Observable = {
  type t('a) = observable('a, {. subscribe: ('a => unit) => unit});
};

type iterable('a);
type unit_fn('a) = Callbag.t('a) => unit;
type nat_fn('a, 'b) = Callbag.t('a) => Callbag.t('b); /* natural transformation */

module Internal = {
  external array_to_iter: array('a) => iterable('a) = "%identity";
};

/* Source factories */
[@bs.module "callbag-basics"]
external from_obs: observable('a, _) => Callbag.t('a) = "fromObs";

[@bs.module "callbag-basics"]
external from_iter: iterable('a) => Callbag.t('a) = "fromIter";

let from_array = arr => arr |> Internal.array_to_iter |> from_iter;

[@bs.module "callbag-basics"]
external from_event: (Dom.element, string) => Callbag.t(Dom.event) =
  "fromEvent";

[@bs.module "callbag-basics"]
external from_promise: Js.Promise.t('a) => Callbag.t('a) = "fromPromise";

[@bs.module "callbag-basics"] external interval: int => Callbag.t(int) = "interval";

/* Sink factories */
[@bs.module "callbag-basics"]
external for_each: ('a => unit) => unit_fn('a) = "forEach";

/* Transformation operators */
[@bs.module "callbag-basics"] external map: ('a => 'b) => nat_fn('a, 'b) = "";

[@bs.module "callbag-basics"]
external scan: (('acc, 'e) => 'acc, 'acc) => nat_fn('e, 'acc) = "scan";

[@bs.module "callbag-basics"]
external flatten: Callbag.t(Callbag.t('a)) => Callbag.t('a) = "flatten";

/* Filtering operators */
[@bs.module "callbag-basics"] external take: int => nat_fn('a, 'b) = "take";

[@bs.module "callbag-basics"] external skip: int => nat_fn('a, 'b) = "skip";

[@bs.module "callbag-basics"]
external filter: ('a => bool) => nat_fn('a, 'b) = "filter";

/* Combination operators */
[@bs.module "callbag-merge"]
external merge: (Callbag.t('a), Callbag.t('a)) => Callbag.t('a) = "default";

[@bs.module "callbag-basics"]
external concat: (Callbag.t('a), Callbag.t('a)) => Callbag.t('a) = "concat";

[@bs.module "callbag-basics"]
external combine: (Callbag.t('a), Callbag.t('b)) => Callbag.t(('a, 'b)) =
  "combine";

/* Utilities */
[@bs.module "callbag-basics"]
external share: Callbag.t('a) => Callbag.t('a) = "share";
