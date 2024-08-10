Pod::Spec.new do |s|
  s.name             = 'TruID'
  s.version          = '3.0.0'
  s.summary          = 'TruID, an identity verification framework.'
  s.description      = <<-DESC
                       TruID is an identity verification framework that provides a simple and secure way to verify the identity of your users. It uses the latest in machine learning and computer vision to provide a seamless experience for your users.
                          DESC
  s.homepage         = 'https://github.com/truid-ai/TruIDPackage'
  s.author           = { 'Hamza' => 'muhammadhamzam1486@gmail.com' }
  s.source           = { :git => 'https://github.com/truid-ai/TruIDPackage.git', :branch => 'test-pods' }
  s.platform         = :ios, '15.0'
  s.requires_arc     = true

  # Specify the dependencies for YourFramework
  s.dependency 'TensorFlowLiteSwift'
  s.dependency 'TensorFlowLiteTaskVision'

  # Specify the location of the framework
  s.vendored_frameworks = 'TruID.xcframework'

  # Frameworks
  s.frameworks = 'SwiftUI'

  # Pods
  s.pod_target_xcconfig = { 'DEFINES_MODULE' => 'YES',
                            'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }
  s.user_target_xcconfig = { 'EXCLUDED_ARCHS[sdk=iphonesimulator*]' => 'arm64' }

  # This indicates whether the module defines a library product or an app product.
  s.module_name = 'TruID'
end
