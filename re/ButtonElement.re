external buttonElement : ReasonReact.reactClass = "Button" [@@bs.module "react-native-elements"];

/*
 buttonStyle={{ marginTop: 8 }}
    title='Submit'
    backgroundColor='#8e8e8e'
    onPress={this.submit}
 */
let make
    buttonStyle::(buttonStyle: Js.t {. marginTop : int})
    title::(title: string)
    backgroundColor::(backgroundColor: string)
    onPress::(onPress: unit => unit)
    children =>
  ReasonReact.wrapJsForReason
    reactClass::buttonElement
    props::{
      "buttonStyle": buttonStyle,
      "title": title,
      "backgroundColor": backgroundColor,
      "onPress": onPress
    }
    children;
