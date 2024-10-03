#include <iostream>

#include "edsdk++/edsdkpp.hpp"


int main()
{
	try {
		edsdkpp::Edsdkpp sdk;
		auto cameraList = sdk.CameraList();

		auto cameraListCount = cameraList.Count();

		if ( 0 == cameraListCount ) {
			std::cout << "no camera(s) detected" << std::endl;
			return -1;
		}

		for ( EdsUInt32 i = 0; i < cameraListCount; ++i ) {
			auto camera = cameraList.Camera( i );
			std::cout << camera.ProductName() << std::endl;

			camera.ObjectEventHandler( []( EdsObjectEvent inEvent, const edsdkpp::HasRef & inRef ) {
				std::cout << "ObjectEventHandler: inEvent = " << inEvent << '\n';
			} );

			camera.PropertyEventHandler( []( EdsPropertyEvent inEvent, EdsPropertyID inPropertyID, EdsUInt32 inParam ) {
				std::cout << "PropertyEventHandler: inEvent = " << inEvent << ", "
						  << "inPropertyID = " << inPropertyID << ", "
						  << "inParam = " << inParam << '\n';
			} );

			camera.enableProperty( kEdsPropID_AutoPowerOffSetting );
			camera.openSession();

			std::cout << "movie param(s)" << std::endl;

			for ( auto d : camera.PropertyDesc( kEdsPropID_MovieParam ) ) {
				std::cout << "0x" << std::hex << d << ", ";
			}

			std::cout << std::endl;

			camera.closeSession();
		}
	}
	catch ( const std::exception & x ) {
		std::cerr << x.what() << std::endl;
	}

	return 0;
}
