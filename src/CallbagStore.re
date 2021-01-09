type store('state, 'action) = {
  get_state: unit => 'state,
  dispatch: 'action => unit,
  store: Callbag.t('state),
};

module Internal = {
  type t('state, 'action);

  [@bs.module "callbag-store"]
  external make:
    ([@bs.uncurry] (('state, 'action) => 'state), 'state) =>
    t('state, 'action) =
    "createStore";

  [@bs.send] external getState: (t('state, 'action), unit) => 'state;
  [@bs.send] external dispatch: (t('state, 'action), 'action) => unit;
  [@bs.get] external store: t('state, 'action) => Callbag.t('state);
};

let make = (reducer, initial_state) => {
  let store = Internal.make(reducer, initial_state);
  {
    get_state: () => Internal.getState(store, ()),
    dispatch: action => Internal.dispatch(store, action),
    store: Internal.store(store),
  };
};
