type store('state, 'action) = {
  get_state: unit => 'state,
  dispatch: 'action => unit,
  store: Callbag.t('state),
};

let make: (('state, 'action) => 'state, 'state) => store('state, 'action);
