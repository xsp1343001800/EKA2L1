/*
 * Copyright (c) 2020 EKA2L1 Team
 * 
 * This file is part of EKA2L1 project
 * (see bentokun.github.com/EKA2L1).
 * 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <system/epoc.h>
#include <services/sisregistry/sisregistry.h>

#include <utils/consts.h>
#include <utils/err.h>

#include <common/chunkyseri.h>

namespace eka2l1 {

    sisregistry_server::sisregistry_server(eka2l1::system *sys)
        : service::typical_server(sys, "!SisRegistryServer") {
    }

    void sisregistry_server::connect(service::ipc_context &context) {
        create_session<sisregistry_client_session>(&context);
        context.complete(epoc::error_none);
    }

    sisregistry_client_session::sisregistry_client_session(service::typical_server *serv, const kernel::uid ss_id,
        epoc::version client_version)
        : service::typical_session(serv, ss_id, client_version) {
    }

    void sisregistry_client_session::fetch(service::ipc_context *ctx) {
        switch (ctx->msg->function) {
        case sisregistry_package_augmentations: {
            request_package_augmentations(ctx);
            break;
        }

        default:
            LOG_ERROR(SERVICE_SISREGISTRY, "Unimplemented opcode for sisregistry server 0x{:X}", ctx->msg->function);
            ctx->complete(epoc::error_none);
            break;
        }
    }

    void sisregistry_client_session::request_package_augmentations(eka2l1::service::ipc_context *ctx) {
        common::chunkyseri seri(nullptr, 0, common::chunkyseri_mode::SERI_MODE_MEASURE);
        populate_augmentations(seri);

        std::vector<char> buf(seri.size());
        seri = common::chunkyseri(reinterpret_cast<std::uint8_t *>(&buf[0]), buf.size(),
            common::SERI_MODE_WRITE);

        ctx->write_data_to_descriptor_argument(0, reinterpret_cast<std::uint8_t *>(&buf[0]), buf.size());
        ctx->complete(epoc::error_none);
    }

    void sisregistry_client_session::populate_augmentations(common::chunkyseri& seri) {
        std::uint32_t property_count = 1;
        seri.absorb(property_count);
        for (size_t i = 0; i < property_count; i++) {
            sisregistry_package package;
            seri.absorb(package.uid);
            epoc::absorb_des(&package.package_name, seri);
            epoc::absorb_des(&package.vendor_name, seri);
            seri.absorb(package.index);
        }
    }

}
