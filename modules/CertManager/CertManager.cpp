//
// Created by CatMoe on 2022/7/12.
//

#include "CertManager.h"
#include <iostream>

#include <openssl/pem.h>
#include <openssl/pkcs12.h>
#include <openssl/x509.h>

void CertManager::CertManagerInit() {
    generateCert();
}
void CertManager::generateCert() {
    // 生成Key

    // 分配内存
    EVP_PKEY *pkey = EVP_PKEY_new();
    if (!pkey) {
        std::cerr << "Create EVP_PKEY failed" << std::endl;
        return;
    }
    std::cout << "PKEY created" << std::endl;


    // 生成Key并处理
    RSA *rsa = RSA_generate_key(2048, RSA_F4, NULL, NULL);
    if (!EVP_PKEY_assign_RSA(pkey, rsa)) {
        std::cerr << "Generate RSA failed" << std::endl;
        EVP_PKEY_free(pkey);
        return;
    }

    std::cout << "REA key created" << std::endl;

    // 生成X509证书
    // 分配内存
    X509 *x509 = X509_new();
    if (!x509) {
        std::cerr << "Create X509 failed" << std::endl;
        return;
    }

    // 设置序列码
    ASN1_INTEGER_set(X509_get_serialNumber(x509), 1);

    // 设置过期时间
    X509_gmtime_adj(X509_get_notBefore(x509), 0);
    X509_gmtime_adj(X509_get_notAfter(x509), 31536000L);

    // 设置公钥
    X509_set_pubkey(x509, pkey);

    X509_NAME * name = X509_get_subject_name(x509);

    X509_NAME_add_entry_by_txt(name, "C",  MBSTRING_ASC, (unsigned char *)"CA",        -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "O",  MBSTRING_ASC, (unsigned char *)"MyCompany", -1, -1, 0);
    X509_NAME_add_entry_by_txt(name, "CN", MBSTRING_ASC, (unsigned char *)"localhost", -1, -1, 0);

    X509_set_issuer_name(x509, name);

    std::cout << "X509 cert created" << std::endl;

    // 用key给证书签名
    if(!X509_sign(x509, pkey, EVP_sha1()))
    {
        std::cerr << "Sign certificate failed" << std::endl;
        X509_free(x509);
        return;
    }

    std::cout << "X509 cert signed" << std::endl;

    // 将证书和key写入
    PKCS12 *pkcs12 = PKCS12_create("CatMoe", NULL, pkey, x509, NULL, 0,0,0,0,0);
    if (pkcs12 == NULL) {
        std::cerr << "Create PKCS12 failed" <<std::endl;
        return;
    }

    std::cout << "PKCS12 cert created" << std::endl;

    FILE *pkcs12file = fopen("./cert/cert.p12", "w");
    int bytes = i2d_PKCS12_fp(pkcs12file, pkcs12);
    if (bytes <= 0) {
        std::cerr << "Write PKCS12 to file failed" <<std::endl;
        return;
    }
    std::cout << "PKCS12 file write success" << std::endl;
    fclose(pkcs12file);
    PKCS12_free(pkcs12);
    X509_free(x509);
    EVP_PKEY_free(pkey);

}