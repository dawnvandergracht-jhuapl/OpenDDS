/*
 *
 *
 * Distributed under the OpenDDS License.
 * See: http://www.opendds.org/license.html
 */

#include "dds/DdsDcpsInfoUtilsC.h"
#include "dds/DdsSecurityCoreC.h"

#ifndef OPENDDS_SECURITY_WRAPPERS_H
#define OPENDDS_SECURITY_WRAPPERS_H

namespace OpenDDS {
  namespace Security {

    struct DiscoveredWriterData_SecurityWrapper {
      OpenDDS::DCPS::DiscoveredWriterData data;
      DDS::Security::EndpointSecurityInfo security_info;
      DDS::Security::DataTags data_tags;
    };

    struct DiscoveredReaderData_SecurityWrapper {
      OpenDDS::DCPS::DiscoveredReaderData data;
      DDS::Security::EndpointSecurityInfo security_info;
      DDS::Security::DataTags data_tags;
    };

    struct SPDPdiscoveredParticipantData_SecurityWrapper {
      OpenDDS::RTPS::SPDPdiscoveredParticipantData data;
      DDS::Security::IdentityToken identity_token;
      DDS::Security::PermissionsToken permissions_token;
      DDS::Security::PropertyQosPolicy property_qos;
      DDS::Security::ParticipantSecurityInfo security_info;
      DDS::Security::IdentityStatusToken identity_status_token;
    };

  }
}

#endif
