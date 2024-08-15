# TruID SDK iOS

## Table of Contents

- [TruID SDK iOS](#truid-sdk-ios)
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
	from: "4.2.0"
)
```

Or:

1. Click on `File` menu
2. Select `Add Package Dependencies...`
3. Paste this `https://github.com/truid-ai/TruIDPackage.git` inside the search bar
4. Select target as your project
5. Add it, and you are good to go.

### Using the `xcframework`

1. Download the `xcframework` from the releases, or by downloading this repository as zip ([click here to download zip](https://github.com/truid-ai/TruIDPackage/archive/refs/heads/main.zip))
2. Drag and drop the framework to your project and start using TruID's SDK for identity verification.

## Sample Code

Following are sample codes for using our SDK, if you are unable to find yours, you may leave an issue. Coming soon for other ways.

### In SwiftUI:

The following code uses `Alamofire` version `5.x.x`

```swift
import Alamofire
import SwiftUI
import TruID

struct  Main: View {
	@State  var  token: String?
	@State var session: TruID.SessionResult?
	@State var error: String? = nil
	@State  var  isFetchingToken = false
	private  let  API_URL = "<api-url-provided-by-our-team>"
	private  let  CLIENT_SECRET = "<your-secret>"

	var body: some View {
		if token == nil {
			VStack {
				Text("TruID iOS SDK Demo")
					.font(.title)
					.padding(.top)

				Spacer()

				Button {
					generateToken(recaptchaToken: "") { response in
						self.token = response.value!.token
					}
				} label: {

					HStack {
						if isFetchingToken {
							ProgressView()
								.foregroundStyle(.white)
								.padding(.horizontal, 4)
						} else {
							Image(systemName: "shield.lefthalf.filled")
								.foregroundColor(.white)
								.font(.title2)
								.frame(alignment: .leading)
						}

						Text("Authenticate with TruID")
							.foregroundColor(.white)
							.font(.title3)
					}
					.frame(maxWidth: .infinity, alignment: .center)
					.padding(.vertical, 8)
					.background(.blue)
					.background(in: RoundedRectangle(cornerRadius: 50))
					.padding()
				}
				.buttonStyle(.plain)
			}
			.alert("Something wrong with your internet", isPresented: $showErrorDialog) {
				Button("OK", role: .cancel) {
					showErrorDialog = false
				}
			}

			if let error {
				Text("Error while creating session")
				Text(error)
			}

		} else {
			TruidMain(
				token: token!,
				API_URL: API_URL,
				face_liveness: true,
				document_capture: true,
				extract_data: true,
				document_authenticity: true,
				document_backside_capture: true,
				id_to_selfie_matching: true,
				fingerprint_capture: true,
				fingerprint_selection: true,
				fingerprint_to_scan: .RIGHT_THUMB,
				enableHelpScreens: true,
				enableReportScreen: true,
				themeColor: Color(UIColor(red: 2/255, green: 131/255, blue: 203/255, alpha: 1.0)),
				success: { sessionResult in
					self.session = sessionResult
					self.token = nil
				},
				failure: { error in
					print(error)
					self.token = nil
					self.error = error.message
				}
			)
		}
	}


	func  generateToken(recaptchaToken: String, success: @escaping (AFDataResponse<GenerateTokenResponse>) -> Void) {
		DispatchQueue(label: "ai.truid.sdkdemotruidapiqueue").async { [self] in
		    DispatchQueue.main.async { isFetchingToken = true }

            let headers: HTTPHeaders = [
                "Authorization": "Api-Key \(CLIENT_SECRET)",
                //  "Authorization": "Api-Token \(CLIENT_SECRET)"
            ]
            let payload = GenerateTokenRequest(token: recaptchaToken, platform: "ios")
            AF.request(
                "\(API_URL)/generate-token/",
                method: .post,
                parameters: payload,
                headers: headers
            )
            .responseDecodable(of: GenerateTokenResponse.self) { response in
                if let error = response.error {
                    showErrorDialog = true
                } else {
                    print(response.value!)
                    self.token = response.value!.token
                    success(response)
                }
            }

		    DispatchQueue.main.async { isFetchingToken = false }
	    }
    }
}

struct  GenerateTokenRequest: Codable {
    let token: String
    let platform: String
}

struct  GenerateTokenResponse: Codable {
    let token: String
}
```

## NOTE

You may remove all the dependencies like `TensorFlowLiteSwift`, `TensorFlowLiteTaskVision`, or any other that you previously installed just because it is the requirement of `TruID` SDK.
