external buttonElement : ReasonReact.reactClass = "Button" [@@bs.module "react-native-elements"];

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
