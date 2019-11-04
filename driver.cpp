#include "driver.h"
#include <fuzzing/datasource/id.hpp>
#include "tests.h"
#include "executor.h"
#include <cryptofuzz/util.h>
#include <set>
#include <unistd.h>

namespace cryptofuzz {

void Driver::LoadModule(std::shared_ptr<Module> module) {
    modules[module->ID] = module;
}

void Driver::Run(const uint8_t* data, const size_t size) const {
    using fuzzing::datasource::ID;

    static ExecutorDigest executorDigest(CF_OPERATION("Digest"), modules, debug);
    static ExecutorHMAC executorHMAC(CF_OPERATION("HMAC"), modules, debug);
    static ExecutorCMAC executorCMAC(CF_OPERATION("CMAC"), modules, debug);
    static ExecutorSymmetricEncrypt executorSymmetricEncrypt(CF_OPERATION("SymmetricEncrypt"), modules, debug);
    static ExecutorSymmetricDecrypt executorSymmetricDecrypt(CF_OPERATION("SymmetricDecrypt"), modules, debug);
    static ExecutorKDF_SCRYPT executorKDF_SCRYPT(CF_OPERATION("KDF_SCRYPT"), modules, debug);
    static ExecutorKDF_HKDF executorKDF_HKDF(CF_OPERATION("KDF_HKDF"), modules, debug);
    static ExecutorKDF_TLS1_PRF executorKDF_TLS1_PRF(CF_OPERATION("KDF_TLS1_PRF"), modules, debug);
    static ExecutorKDF_PBKDF1 executorKDF_PBKDF1(CF_OPERATION("KDF_PBKDF1"), modules, debug);
    static ExecutorKDF_PBKDF2 executorKDF_PBKDF2(CF_OPERATION("KDF_PBKDF2"), modules, debug);
    static ExecutorKDF_ARGON2 executorKDF_ARGON2(CF_OPERATION("KDF_ARGON2"), modules, debug);
    static ExecutorKDF_SSH executorKDF_SSH(ID("Cryptofuzz/Operation/KDF_SSH"), modules, debug);
    static ExecutorKDF_X963 executorKDF_X963(CF_OPERATION("KDF_X963"), modules, debug);

    try {

        Datasource ds(data, size);

        const auto operation = ds.Get<uint64_t>();
        const auto payload = ds.GetData(0, 1);

        switch ( operation ) {
            case CF_OPERATION("Digest"):
                executorDigest.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("HMAC"):
                executorHMAC.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("CMAC"):
                executorCMAC.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("SymmetricEncrypt"):
                executorSymmetricEncrypt.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("SymmetricDecrypt"):
                executorSymmetricDecrypt.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_SCRYPT"):
                executorKDF_SCRYPT.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_HKDF"):
                executorKDF_HKDF.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_TLS1_PRF"):
                executorKDF_TLS1_PRF.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_PBKDF1"):
                executorKDF_PBKDF1.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_PBKDF2"):
                executorKDF_PBKDF2.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_ARGON2"):
                executorKDF_ARGON2.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_SSH"):
                executorKDF_SSH.Run(ds, payload.data(), payload.size());
                break;
            case CF_OPERATION("KDF_X963"):
                executorKDF_X963.Run(ds, payload.data(), payload.size());
                break;
#if 0
            case    ID("Cryptofuzz/Operation/Sign"):
                executorSign.Run(ds, payload.data(), payload.size());
                break;
            case    ID("Cryptofuzz/Operation/Verify"):
                executorVerify.Run(ds, payload.data(), payload.size());
                break;
#endif
        }
    } catch ( Datasource::OutOfData ) {
    }
};

Driver::Driver(const bool debug) :
    debug(debug)
{ }

} /* namespace cryptofuzz */
