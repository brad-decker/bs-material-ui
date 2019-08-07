[@bs.deriving jsConverter]
type maxWidth = [
  | [@bs.as "xs"] `Xs
  | [@bs.as "sm"] `Sm
  | [@bs.as "md"] `Md
  | [@bs.as "lg"] `Lg
  | [@bs.as "xl"] `Xl
  | [@bs.as "false"] `False
];

module Classes = {
  type classesType =
    | Root(string)
    | Fixed(string)
    | MaxWidthXs(string)
    | MaxWidthSm(string)
    | MaxWidthMd(string)
    | MaxWidthLg(string)
    | MaxWidthXl(string);
  type t = list(classesType);
  let to_string =
    fun
    | Root(_) => "root"
    | Fixed(_) => "fixed"
    | MaxWidthXs(_) => "maxWidthXs"
    | MaxWidthSm(_) => "maxWidthSm"
    | MaxWidthMd(_) => "maxWidthMd"
    | MaxWidthLg(_) => "maxWidthLg"
    | MaxWidthXl(_) => "maxWidthXl";
  let to_obj = listOfClasses =>
    listOfClasses->(
                     Belt.List.reduce(
                       Js.Dict.empty(),
                       (obj, classType) => {
                         switch (classType) {
                         | Root(className)
                         | Fixed(className)
                         | MaxWidthXs(className)
                         | MaxWidthSm(className)
                         | MaxWidthMd(className)
                         | MaxWidthLg(className)
                         | MaxWidthXl(className) =>
                           Js.Dict.set(obj, to_string(classType), className)
                         };
                         obj;
                       },
                     )
                   );
};

[@bs.obj]
external makePropsMui:
  (
    ~children: 'children=?,
    ~className: string=?,
    ~fixed: bool=?,
    ~maxWidth: string=?,
    ~key: string=?,
    ~_ref: React.Ref.t(option(Dom.element))=?,
    ~classes: Js.Dict.t(string)=?,
    ~style: ReactDOMRe.Style.t=?,
    unit
  ) =>
  _ =
  "";

let makeProps =
    (
      ~children: option('children)=?,
      ~className: option(string)=?,
      ~fixed: option(bool)=?,
      ~maxWidth: option(maxWidth)=?,
      ~key: option(string)=?,
      ~ref_: option(React.Ref.t(option(Dom.element)))=?,
      ~classes: option(Classes.t)=?,
      ~style: option(ReactDOMRe.Style.t)=?,
      (),
    ) =>
  makePropsMui(
    ~children?,
    ~className?,
    ~fixed?,
    ~maxWidth=?maxWidth->(Belt.Option.map(v => maxWidthToJs(v))),
    ~key?,
    ~_ref=?ref_,
    ~classes=?Belt.Option.map(classes, v => Classes.to_obj(v)),
    ~style?,
    (),
  );

[@bs.module "@material-ui/core"]
external make: React.component('a) = "Container";