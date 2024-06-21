#ifndef BOOTLOADER_SLOTS_USERLAND_HEADER_H
#define BOOTLOADER_SLOTS_USERLAND_HEADER_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>

namespace Bootloader {

class UserlandHeader {
public:
  const char * version() const;
  const bool isValid() const;
  const bool isOmega() const;
  const char * omegaVersion() const;
  const bool isUpsilon() const;
  const char * upsilonVersion() const;
  const bool isMu() const;
  const char * muVersion() const;
  const void * storageAddress() const;
  const size_t storageSize() const;

private:
  UserlandHeader();
  constexpr static uint32_t Magic = 0xDEC0EDFE;
  constexpr static uint32_t OmegaMagic = 0xEFBEADDE;
  constexpr static uint32_t UpsilonMagic = 0x55707369;
  constexpr static uint32_t MuMagic = 0x7E008D69;
  uint32_t m_header;
  const char m_expectedEpsilonVersion[8];
  void * m_storageAddressRAM;
  size_t m_storageSizeRAM;
  /* We store the range addresses of external apps memory because storing the
   * size is complicated due to c++11 constexpr. */
  uint32_t m_externalAppsFlashStart;
  uint32_t m_externalAppsFlashEnd;
  uint32_t m_externalAppsRAMStart;
  uint32_t m_externalAppsRAMEnd;
  uint32_t m_footer;
  uint32_t m_omegaMagicHeader;
  const char m_omegaVersion[16];
  const volatile char m_username[16];
  uint32_t m_omegaMagicFooter;
  uint32_t m_upsilonMagicHeader;
  const char m_UpsilonVersion[16];
  uint32_t m_osType;
  uint32_t m_upsilonMagicFooter;
  uint32_t m_muMagicHeader;
  const char m_MuVersion[16];
  uint32_t m_muMagicFooter;
};

extern const UserlandHeader* s_userlandHeaderA;
extern const UserlandHeader* s_userlandHeaderB;

}

#endif
