open ReactNative;

/*
   import { Button } from 'react-native-elements';
   import { addCity, updateAsyncStorage } from '../../actions/citiesActions';
   import { connect } from 'react-redux'; */
let windowWidth = ((Dimensions.get `window)##width);

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
  | ChangeCountry string;

type input = {
  city: string,
  country: string
};

type state = {
  input,
  nameRef: ref (option ReasonReact.reactRef)
};

let setNameRef theRef {ReasonReact.state: state} => state.nameRef := Js.Null.to_opt theRef;

let component = ReasonReact.reducerComponent "TabAddCity";

let make ::_message _children => {
  ...component,
  initialState: fun () => {input: {city: "", country: ""}, nameRef: ref None},
  reducer: fun action state =>
    switch action {
    | ChangeCity city => ReasonReact.Update {...state, input: {...state.input, city}}
    | ChangeCountry country => ReasonReact.Update {...state, input: {...state.input, country}}
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
        value=self.state.input.city
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
    </View>
};

/*
   <Button
   buttonStyle={{ marginTop: 8 }}
   title='Submit'
   backgroundColor='#8e8e8e'
   onPress={this.submit}
 />
 */
let tabAddCity =
  ReasonReact.wrapReasonForJs ::component (fun jsProps => make _message::jsProps##_message [||]);
/* class CitiesTab extends React.Component {
     state = {
       input: {}
     }
     updateInput = (key, value) => {
       this.setState({
         input: {
           ...this.state.input,
           [key]: value,
         }
       })
     }
     submit = () => {
       if (!this.state.input['country'] || !this.state.input['name']) return
       const { dispatchAddCity } = this.props;
       dispatchAddCity(this.state.input)
       this.setState({ input: {} }, () => {
         this.props.dispatchUpdateAsyncStorage();
       })
       this.nameRef.focus()
     }
     render() {
       return (
         <View style=styles.container>
           <Image
             resizeMode='contain'
             style=styles.logo
             source={require('../../assets/citieslogo.png')}
           />
           <TextInput
             ref={name => this.nameRef = name}
             value={this.state.input['name']}
             onChangeText={(value) => this.updateInput('name', value)}
             style=styles.textInput
             placeholder='City name'
             autoCorrect={false}
             underlineColorAndroid='transparent'
           />
           <TextInput
             value={this.state.input['country']}
             onChangeText={(value) => this.updateInput('country', value)}
             style=styles.textInput
             placeholder='Country name'
             autoCorrect={false}
             underlineColorAndroid='transparent'
           />
           <Button
             buttonStyle={{ marginTop: 8 }}
             title='Submit'
             backgroundColor='#8e8e8e'
             onPress={this.submit}
           />
         </View>
       )
     }
   }

   const mapDispatchToProps = (dispatch) => ({
     dispatchAddCity: (city) => dispatch(addCity(city)),
     dispatchUpdateAsyncStorage: () => dispatch(updateAsyncStorage()),
   });

   export default connect(null, mapDispatchToProps)(CitiesTab) */
