# TruID SDK iOS offline Fingerprints

## Table of Contents

- [TruID SDK iOS offline Fingerprints](#truid-sdk-ios-offline-fingerprints)
  - [Table of Contents](#table-of-contents)
  - [Building trust through robust Identity Verification](#building-trust-through-robust-identity-verification)
  - [Installing TruID SDK in your iOS project](#installing-truid-sdk-in-your-ios-project)
    - [Using Swift Package Manager](#using-swift-package-manager)
    - [Using the `xcframework`](#using-the-xcframework)
  - [Sample Code](#sample-code)
    - [In SwiftUI:](#in-swiftui)
  - [NOTE](#note)

## Building trust through robust Identity Verification

At truID, we provide identity verification solutions that enable businesses to establish trust with their customers. We help businesses to verify the identity of an individual remotely in less than 30 seconds, drastically reducing onboarding time and cost.

## Installing TruID SDK in your iOS project

Following are two ways of integrating our SDK in your project.

### Using Swift Package Manager

Add this to your Package.swift

```swift
.package(
	url: "https://github.com/truid-ai/TruIDPackage.git",
	.branch("nadra")
)
```

Or:

1. Click on `File` menu
2. Select `Add Package Dependencies...`
3. Paste this `https://github.com/truid-ai/TruIDPackage.git` inside the search bar
4. Select the branch `nadra`
5. Select target as your project
6. Add it, and you are good to go.

### Using the `xcframework`

1. Download the `xcframework` from the releases, or by downloading this repository as zip ([click here to download zip](https://github.com/truid-ai/TruIDPackage/archive/refs/heads/main.zip))
2. Drag and drop the framework to your project and start using TruID's SDK for identity verification.
3. Embed the framework in your project.

## Sample Code

Following are sample codes for using our SDK, if you are unable to find yours, you may leave an issue. Coming soon for other ways.

### In SwiftUI:

```swift
import SwiftUI
import TruID

struct ContentView: View {
    @State var token: String?
    @State var session: TruID.SessionResult?
    @State var error: String? = nil

    var body: some View {
        if token == nil {
            VStack(alignment: .leading) {
                Text("TruID iOS SDK Demo")
                    .font(.title)
                    .padding(.top)
                    .padding(.bottom, 20)

                if let session {
                    let fingerprintsData = session.fingerprintsData
                    let livenessData = session.livenessData
                    ScrollView {
                        VStack(alignment: .leading, spacing: 20) {
                            VStack(alignment: .leading) {
                                Text("Left Hand")
                                    .font(.title3)

                                Text("Finger 1: \(fingerprintsData.finger1.NFIQ)")
                                Text("Finger 2: \(fingerprintsData.finger2.NFIQ)")
                                Text("Finger 3: \(fingerprintsData.finger3.NFIQ)")
                                Text("Finger 4: \(fingerprintsData.finger4.NFIQ)")
                                Text("Finger 5: \(fingerprintsData.finger5.NFIQ)")
                            }

                            VStack(alignment: .leading) {
                                Text("Right Hand")
                                    .font(.title3)

                                Text("Finger 6: \(fingerprintsData.finger6.NFIQ)")
                                Text("Finger 7: \(fingerprintsData.finger7.NFIQ)")
                                Text("Finger 8: \(fingerprintsData.finger8.NFIQ)")
                                Text("Finger 9: \(fingerprintsData.finger9.NFIQ)")
                                Text("Finger 10: \(fingerprintsData.finger10.NFIQ)")
                            }

                            VStack(alignment: .leading) {
                                Text("Liveness")
                                    .font(.title3)

                                Text("Right 4: \(livenessData.right4)")
                                Text("Left 4: \(livenessData.left4)")
                                Text("Right Thumb: \(livenessData.rightThumb)")
                                Text("Left Thumb: \(livenessData.leftThumb)")
                            }
                        }
                        .onAppear {
                            print(session.fingerprintsData)
                            print(session.livenessData)
                        }
                    }
                }

                Spacer()

                Button {
                    self.token = ""
                } label: {
                    HStack {
                        Image(systemName: "shield.lefthalf.filled")
                            .foregroundColor(.white)
                            .font(.title2)
                            .frame(alignment: .leading)
                        Text("Authenticate with TruID")
                            .foregroundColor(.white)
                            .font(.title3)
                    }
                    .frame(maxWidth: .infinity, alignment: .center)
                    .padding(.vertical, 8)
                    .background(.blue)
                    .background(in: RoundedRectangle(cornerRadius: 50))
                    .foregroundStyle(.white)
                }
                .buttonStyle(.plain)

                if session == nil {
                    Spacer()
                }
            }
            .padding()
            if let error {
                Text("Error while creating session")
                Text(error)
            }
        } else {
            TruidMain(
                fingerprint_capture: true,
                fingerprint_selection: true,
                fingerprint_liveness: true,
                fingerprint_to_scan: .LEFT_4_RIGHT_4,
                enableHelpScreens: true,
                themeColor: Color(UIColor(red: 2/255, green: 131/255, blue: 203/255, alpha: 1.0))
            ) { sessionResult in
                self.session = sessionResult
                self.token = nil
            } failure: { error in
                print(error)
                self.token = nil
                self.error = error
            }
        }
    }
}
```

## NOTE

You may remove all the dependencies like `TensorFlowLiteSwift`, `TensorFlowLiteTaskVision`, or any other that you previously installed just because it is the requirement of `TruID` SDK.
