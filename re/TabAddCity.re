open ReactNative;

/*
 import { Button } from 'react-native-elements';
 import { addCity, updateAsyncStorage } from '../../actions/citiesActions';
 import { connect } from 'react-redux'; */
let windowWidth = (Dimensions.get `window)##width;

let styles =
  StyleSheet.create
    Style.(
      {
        "container": style [flex 1., backgroundColor "#9C27B0"],
        "logo":
          style [
            maxHeight 36.,
            maxWidth (float_of_int windowWidth),
            marginTop 100.,
            alignItems `center
          ],
        "textInput":
          style [
            height 55.,
            backgroundColor "white",
            marginHorizontal 15.,
            marginTop 8.,
            padding 9.
          ]
      }
    );

type action =
  | ChangeCity string
  | ChangeCountry string
  | Submit;

type input = {
  name: string,
  country: string
};

type state = {
  input,
  nameRef: ref (option ReasonReact.reactRef)
};

type retainedProps = {
  dispatchAddCity: Js.t {. name : string, country : string} => unit,
  dispatchUpdateAsyncStorage: unit => unit
};

let setNameRef theRef {ReasonReact.state: state} => state.nameRef := Js.Null.to_opt theRef;

let component = ReasonReact.reducerComponentWithRetainedProps "TabAddCity";

/*
 submit = () => {
      if (!this.state.input['country'] || !this.state.input['name']) return
      const { dispatchAddCity } = this.props;
      dispatchAddCity(this.state.input)
      this.setState({ input: {} }, () => {
        this.props.dispatchUpdateAsyncStorage();
      })
      this.nameRef.focus()
    }
    */
let make ::dispatchAddCity ::dispatchUpdateAsyncStorage _children => {
  ...component,
  initialState: fun () => {input: {name: "", country: ""}, nameRef: ref None},
  /* retainedProps: {dispatchAddCity: Js.t { city: string, country: string}, dispatchUpdateAsyncStorage: int => int}, */
  retainedProps: {dispatchAddCity, dispatchUpdateAsyncStorage},
  reducer: fun action state =>
    switch action {
    | ChangeCity name => ReasonReact.Update {...state, input: {...state.input, name}}
    | ChangeCountry country => ReasonReact.Update {...state, input: {...state.input, country}}
    | Submit =>
      let {input} = state;
      switch (input.name, input.country) {
      | ("", "") => ReasonReact.NoUpdate
      | (name, country) =>
        ReasonReact.UpdateWithSideEffects
          {...state, input: {name: "", country: ""}}
          (
            fun self => {
              self.retainedProps.dispatchAddCity {"name": name, "country": country};
              self.retainedProps.dispatchUpdateAsyncStorage ();
              ()
            }
          )
          /* ReasonReact.Update state */
      };
    },
  render: fun self =>
    <View style=styles##container>
      <Image
        resizeMode=`contain
        style=styles##logo
        /* source=Image.(Required (Packager.require "../../app/assets/citieslogo.png")) */
        source=Image.(Required (Packager.require "../../../app/assets/citieslogo.png"))
      />
      <TextInput
        ref=(self.handle setNameRef)
        value=self.state.input.name
        /* onChangeText={(value) => this.updateInput('name', value)} */
        onChangeText=(self.reduce (fun value => ChangeCity value))
        style=styles##textInput
        placeholder="City name"
        autoCorrect=false
        underlineColorAndroid="transparent"
      />
      <TextInput
        value=self.state.input.country
        /* onChangeText={(value) => this.updateInput('country', value)} */
        onChangeText=(self.reduce (fun value => ChangeCountry value))
        style=styles##textInput
        placeholder="Country name"
        autoCorrect=false
        underlineColorAndroid="transparent"
      />
      <ButtonElement
        buttonStyle={"marginTop": 8}
        title="Submit"
        backgroundColor="#8e8e8e"
        onPress=(self.reduce (fun _event => Submit))
      />
    </View>
};

let tabAddCity =
  ReasonReact.wrapReasonForJs
    ::component
    (
      fun jsProps =>
        make
          dispatchAddCity::jsProps##dispatchAddCity
          dispatchUpdateAsyncStorage::jsProps##dispatchUpdateAsyncStorage
          [||]
    );
/*
   const mapDispatchToProps = (dispatch) => ({
     dispatchAddCity: (city) => dispatch(addCity(city)),
     dispatchUpdateAsyncStorage: () => dispatch(updateAsyncStorage()),
   });

   export default connect(null, mapDispatchToProps)(CitiesTab) */
