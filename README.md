# WebRTC-SDK

This repository contains a fork of WebRTC from Google with various improvements.

## Main changes

### All

- Dynamically acquire decoder to mitigate decoder limitations [#25](https://github.com/webrtc-sdk/webrtc/pull/25)
- Support for video simulcast with hardware & software encoders [patch](https://github.com/webrtc-sdk/webrtc/commit/ee030264e2274a2c90548a99b448782049e48fb4)
- Frame cryptor support (for end-to-end encryption) [patch](https://github.com/webrtc-sdk/webrtc/commit/3a2c008529a15fecde5f979a6ebb75c05463d45e)

### Android

- WrappedVideoDecoderFactory [#74](https://github.com/webrtc-sdk/webrtc/pull/74)

### iOS / Mac

[native-dev]: https://webrtc.googlesource.com/src/+/main/docs/native-code/
