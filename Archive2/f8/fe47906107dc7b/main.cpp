typedef boost::variant<
    Tags::Metadata::FileAttributes,
    Tags::Metadata::EnableTelemetry,
    Tags::Metadata::DefineBinaryData,
    Tags::DisplayList::PlaceObject,
    Tags::DisplayList::PlaceObject2,
    Tags::DisplayList::PlaceObject3,
    Tags::DisplayList::RemoveObject,
    Tags::DisplayList::RemoveObject2,
    Tags::Control::ShowFrame,
    Tags::Control::SetBackgroundColor,
    Tags::Control::FrameLabel,
    Tags::Control::Protect,
    Tags::Control::End,
    Tags::Control::ExportAssets,
    Tags::Control::ImportAssets,
    Tags::Control::EnableDebugger,
    Tags::Control::EnableDebugger2,
    Tags::Control::ScriptLimits,
    Tags::Control::SetTabIndex,
    Tags::Control::ImportAssets2,
    Tags::Control::SymbolClass,
    Tags::Control::Metadata,
    Tags::Control::DefineScalingGrid,
    Tags::Control::DefineSceneAndFrameLabelData,
    Tags::Shapes::DefineShape,
    Tags::Shapes::DefineShape2,
    Tags::Shapes::DefineShape3,
    Tags::Shapes::DefineShape4,
    Tags::Fonts::DefineFont,
    Tags::Fonts::DefineFontInfo,
    Tags::Fonts::DefineFontInfo2,
    Tags::Fonts::DefineFont2,
    Tags::Fonts::DefineFont3,
    Tags::Fonts::DefineFontAlignZones,
    Tags::Fonts::DefineFontName,
    Tags::StaticText::DefineText,
    Tags::StaticText::DefineText2,
    Tags::DynamicText::DefineEditText,
    Tags::DynamicText::CSMTextSettings,
    Tags::DynamicText::DefineFont4,
    Tags::Sounds::DefineSound,
    Tags::Sounds::StartSound,
    Tags::Sounds::StartSound2,
    Tags::Sounds::SoundStreamHead,
    Tags::Sounds::SoundStreamHead2,
    Tags::Sounds::SoundStreamBlock,
    Tags::Buttons::DefineButton,
    Tags::Buttons::DefineButton2,
    Tags::Buttons::DefineButtonCxform,
    Tags::Buttons::DefineButtonSound,
    Tags::Sprites::DefineSprite,
    Tags::Video::DefineVideoStream,
    Tags::Video::VideoFrame,
    Tags::Actions::SWF3::DoAction,
    Tags::Actions::SWF3::Play,
    Tags::Actions::SWF3::Stop,
    Tags::Actions::SWF3::NextFrame,
    Tags::Actions::SWF3::PreviousFrame,
    Tags::Actions::SWF3::GotoFrame,
    Tags::Actions::SWF3::GotoLabel,
    Tags::Actions::SWF3::WaitForFrame,
    Tags::Actions::SWF3::GetURL,
    Tags::Actions::SWF3::StopSounds,
    Tags::Actions::SWF3::ToggleQuality,
    Tags::Actions::SWF3::SetTarget,
    Tags::Actions::SWF4::Add,
    Tags::Actions::SWF4::Divide,
    Tags::Actions::SWF4::Multiply,
    Tags::Actions::SWF4::Subtract,
    Tags::Actions::SWF4::Equals,
    Tags::Actions::SWF4::Less,
    Tags::Actions::SWF4::And,
    Tags::Actions::SWF4::Not,
    Tags::Actions::SWF4::Or,
    Tags::Actions::SWF4::StringAdd,
    Tags::Actions::SWF4::StringEquals,
    Tags::Actions::SWF4::StringExact,
    Tags::Actions::SWF4::StringLength,
    Tags::Actions::SWF4::MBStringExact,
    Tags::Actions::SWF4::MBStringLength,
    Tags::Actions::SWF4::StringLess,
    Tags::Actions::SWF4::Pop,
    Tags::Actions::SWF4::Push,
    Tags::Actions::SWF4::AsciiToChar,
    Tags::Actions::SWF4::CharToAscii,
    Tags::Actions::SWF4::ToInteger,
    Tags::Actions::SWF4::MBAsciiToChar,
    Tags::Actions::SWF4::MBCharToAscii,
    Tags::Actions::SWF4::Call,
    Tags::Actions::SWF4::If,
    Tags::Actions::SWF4::Jump,
    Tags::Actions::SWF4::GetVariable,
    Tags::Actions::SWF4::SetVariable,
    Tags::Actions::SWF4::GetURL2,
    Tags::Actions::SWF4::GetProperty,
    Tags::Actions::SWF4::GotoFrame2,
    Tags::Actions::SWF4::RemoveSprite,
    Tags::Actions::SWF4::SetProperty,
    Tags::Actions::SWF4::SetTarget2,
    Tags::Actions::SWF4::StartDrag,
    Tags::Actions::SWF4::WaitForFrame2,
    Tags::Actions::SWF4::CloneSprite,
    Tags::Actions::SWF4::EndDrag,
    Tags::Actions::SWF4::Trace,
    Tags::Actions::SWF4::GetTime,
    Tags::Actions::SWF4::RandomNumber,
    Tags::Actions::SWF5::CallFunction,
    Tags::Actions::SWF5::CallMethod,
    Tags::Actions::SWF5::ConstantPool,
    Tags::Actions::SWF5::DefineFunction,
    Tags::Actions::SWF5::DefineLocal,
    Tags::Actions::SWF5::DefineLocal2,
    Tags::Actions::SWF5::Delete,
    Tags::Actions::SWF5::Delete2,
    Tags::Actions::SWF5::Enumerate,
    Tags::Actions::SWF5::Equals2,
    Tags::Actions::SWF5::GetMember,
    Tags::Actions::SWF5::InitArray,
    Tags::Actions::SWF5::InitObject,
    Tags::Actions::SWF5::NewMethod,
    Tags::Actions::SWF5::NewObject,
    Tags::Actions::SWF5::SetMember,
    Tags::Actions::SWF5::TargetPath,
    Tags::Actions::SWF5::With,
    Tags::Actions::SWF5::ToNumber,
    Tags::Actions::SWF5::ToString,
    Tags::Actions::SWF5::TypeOf,
    Tags::Actions::SWF5::Add2,
    Tags::Actions::SWF5::Less2,
    Tags::Actions::SWF5::Modulo,
    Tags::Actions::SWF5::BitAnd,
    Tags::Actions::SWF5::BitLShift,
    Tags::Actions::SWF5::BitOr,
    Tags::Actions::SWF5::BitRShift,
    Tags::Actions::SWF5::BitURShift,
    Tags::Actions::SWF5::Decrement,
    Tags::Actions::SWF5::Increment,
    Tags::Actions::SWF5::PushDuplicate,
    Tags::Actions::SWF5::Return,
    Tags::Actions::SWF5::StackSwap,
    Tags::Actions::SWF5::StoreRegister,
    Tags::Actions::SWF6::DoInitAction,
    Tags::Actions::SWF6::InstanceOf,
    Tags::Actions::SWF6::Enumerate2,
    Tags::Actions::SWF6::StrictEquals,
    Tags::Actions::SWF6::Greater,
    Tags::Actions::SWF6::StringGreater,
    Tags::Actions::SWF7::DefineFunction2,
    Tags::Actions::SWF7::Extends,
    Tags::Actions::SWF7::CastOp,
    Tags::Actions::SWF7::ImplementsOp,
    Tags::Actions::SWF7::Try,
    Tags::Actions::SWF7::Throw,
    Tags::Actions::SWF9::DoABC
> Tag;