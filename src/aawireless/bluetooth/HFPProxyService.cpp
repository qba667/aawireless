//
// Created by chiel on 15-01-20.
//

#include "HFPProxyService.h"
#include "HFPProxyProfile.h"
#include <BluezQt/PendingCall>
#include <aawireless/log/Log.h>

namespace aawireless {
    namespace bluetooth {
        HFPProxyService::HFPProxyService(std::shared_ptr<BluezQt::Manager> btManager) :
                btManager(std::move(btManager)) {
        }

        void HFPProxyService::start() {
            hfpProxyProfile = std::make_shared<HFPProxyProfile>();
            BluezQt::PendingCall *call = btManager->registerProfile(hfpProxyProfile.get());
            connect(call, &BluezQt::PendingCall::finished, this, &HFPProxyService::onProfileReady);
        }

        void HFPProxyService::stop() {
            btManager->unregisterProfile(hfpProxyProfile.get());
        }

        void HFPProxyService::connectToDevice(QString address) {

        }

        void HFPProxyService::onProfileReady(BluezQt::PendingCall *call) {
            if (call->error()) {
                AW_LOG(error) << "Error registering profile" << call->errorText().toStdString();
                return;
            }

            AW_LOG(info) << "HFP profile registered";
        }
    }
}