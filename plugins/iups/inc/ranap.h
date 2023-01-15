/*************************************************************/
/* Copyright (C) 2019 OSS Nokalva, Inc.  All rights reserved.*/
/*************************************************************/

/* THIS FILE IS PROPRIETARY MATERIAL OF OSS NOKALVA, INC.
 * AND MAY BE USED ONLY BY DIRECT LICENSEES OF OSS NOKALVA, INC.
 * THIS FILE MAY NOT BE DISTRIBUTED.
 * THIS COPYRIGHT STATEMENT MAY NOT BE REMOVED. */

/* Generated for: Pinnacle Digital Analytics Pvt Ltd, New Delhi, India - Project Start-up expiring 26 July 2020, License 17395 17395,
 * only for project "Development and support of Mobility Packet Decoder". */
/* Abstract syntax: ranap */
/* Created: Wed Jul 31 10:10:31 2019 */
/* ASN.1/C++ compiler version: 6.7 */
/* Code generated for runtime version 6.7 or later */
/* Compiler operating system: Linux with 64-bit support */
/* Compiler machine type: Intel 64 or AMD64 */
/* Target operating system: Linux with 64-bit support */
/* Target machine type: Intel 64 or AMD64 */
/* C++ compiler options required: -m64 */
/* ASN.1 compiler options and file names specified:
 * -output ranap -externalname ranap -per -root -autoencdec
 * ../../../asn1dflt.cpp.linux-amd64 RANAP-PDU-Descriptions.asn
 * RANAP-CommonDataTypes.asn RANAP-Constants.asn RANAP-Containers.asn
 * RANAP-IEs.asn RANAP-PDU-Contents.asn RANAP-PDU-Sample-Values.asn
 */

#ifndef OSS_ranap
#define OSS_ranap

#include "oss.h"
#include "asn1.h"

/* Representation types */

enum Criticality {
    reject = 0,
    ignore = 1,
    notify = 2
};

enum AccuracyFulfilmentIndicator {
    requested_Accuracy_Fulfilled = 0,
    requested_Accuracy_Not_Fulfilled = 1
};

enum ClientType {
    emergency_Services = 0,
    value_Added_Services = 1,
    pLMN_Operator_Services = 2,
    lawful_Intercept_Services = 3,
    pLMN_Operator_Broadcast_Services = 4,
    pLMN_Operator_O_et_M = 5,
    pLMN_Operator_Anonymous_Statistics = 6,
    pLMN_Operator_Target_MS_Service_Support = 7
};

enum CN_DomainIndicator {
    cs_domain = 0,
    ps_domain = 1
};

enum KeyStatus {
    old = 0,
    KeyStatus_new = 1
};

enum LocationRelatedDataRequestTypeSpecificToGERANIuMode {
    decipheringKeysEOTD = 0,
    dedicatedMobileAssistedEOTDAssistanceData = 1,
    dedicatedMobileBasedEOTDAssistanceData = 2
};

enum NonSearchingIndication {
    non_searching = 0,
    searching = 1
};

enum PagingCause {
    terminating_conversational_call = 0,
    terminating_streaming_call = 1,
    terminating_interactive_call = 2,
    terminating_background_call = 3,
    terminating_low_priority_signalling = 4,
    terminating_high_priority_signalling = 5
};

enum PositioningPriority {
    high_Priority = 0,
    normal_Priority = 1
};

enum RateControlAllowed {
    not_allowed = 0,
    allowed = 1
};

enum RelocationType {
    ue_not_involved = 0,
    ue_involved = 1
};

enum ResponseTime {
    lowdelay = 0,
    delaytolerant = 1
};

enum SAPI {
    sapi_0 = 0,
    sapi_3 = 1
};

enum SignallingIndication {
    signalling = 0
};

enum TypeOfError {
    not_understood = 0,
    missing = 1
};

enum Presence {
    optional = 0,
    conditional = 1,
    mandatory = 2
};

enum TriggeringMessage {
    initiating_message = 0,
    successful_outcome = 1,
    unsuccessfull_outcome = 2,
    outcome = 3
};

enum Pre_emptionCapability {
    shall_not_trigger_pre_emption = 0,
    may_trigger_pre_emption = 1
};

enum Pre_emptionVulnerability {
    not_pre_emptable = 0,
    pre_emptable = 1
};

enum QueuingAllowed {
    queueing_not_allowed = 0,
    queueing_allowed = 1
};

enum Alt_RAB_Parameter_MaxBitrateType {
    Alt_RAB_Parameter_MaxBitrateType_unspecified = 0,
    Alt_RAB_Parameter_MaxBitrateType_value_range = 1,
    Alt_RAB_Parameter_MaxBitrateType_discrete_values = 2
};

enum Alt_RAB_Parameter_GuaranteedBitrateType {
    Alt_RAB_Parameter_GuaranteedBitrateType_unspecified = 0,
    Alt_RAB_Parameter_GuaranteedBitrateType_value_range = 1,
    Alt_RAB_Parameter_GuaranteedBitrateType_discrete_values = 2
};

enum DataVolumeReportingIndication {
    do_report = 0,
    do_not_report = 1
};

enum DeliveryOfErroneousSDU {
    yes = 0,
    no = 1,
    no_error_detection_consideration = 2
};

enum DeliveryOrder {
    delivery_order_requested = 0,
    delivery_order_not_requested = 1
};

enum Event {
    stop_change_of_service_area = 0,
    direct = 1,
    change_of_servicearea = 2,
    stop_direct = 3
};

enum _enum1 {
    north = 0,
    south = 1
};

enum _enum2 {
    height = 0,
    depth = 1
};

enum _enum3 {
    iu_cs = 0,
    iu_ps = 1,
    iur = 2,
    iub = 3,
    uu = 4
};

enum RequestedLocationRelatedDataType {
    decipheringKeysUEBasedOTDOA = 0,
    decipheringKeysAssistedGPS = 1,
    dedicatedAssistanceDataUEBasedOTDOA = 2,
    dedicatedAssistanceDataAssistedGPS = 3
};

enum PDP_Type {
    empty = 0,
    ppp = 1,
    osp_ihoss = 2,
    ipv4 = 3,
    ipv6 = 4
};

enum RAB_AsymmetryIndicator {
    symmetric_bidirectional = 0,
    asymmetric_unidirectional_downlink = 1,
    asymmetric_unidirectional_uplink = 2,
    asymmetric_bidirectional = 3
};

enum TrafficClass {
    conversational = 0,
    streaming = 1,
    interactive = 2,
    background = 3
};

enum SourceStatisticsDescriptor {
    speech = 0,
    unknown = 1
};

enum RelocationRequirement {
    lossless = 0,
    none = 1,
    realtime = 2
};

enum ReportArea {
    service_area = 0,
    geographical_area = 1
};

enum _enum4 {
    activated = 0,
    deactivated = 1
};

enum Service_Handover {
    handover_to_GSM_should_be_performed = 0,
    handover_to_GSM_should_not_be_performed = 1,
    handover_to_GSM_shall_not_be_performed = 2
};

enum TraceDepth {
    minimum = 0,
    medium = 1,
    maximum = 2
};

enum UserPlaneMode {
    transparent_mode = 0,
    support_mode_for_predefined_SDU_sizes = 1
};


const OSS_UINT32 no_encryption = 0;
const OSS_UINT32 standard_UMTS_encryption_algorith_UEA1 = 1;

const OSS_UINT32 standard_UMTS_integrity_algorithm_UIA1 = 0;
const OSS_UINT32 no_value = 15;

const OSS_UINT32 PriorityLevel_spare = 0;
const OSS_UINT32 PriorityLevel_highest = 1;
const OSS_UINT32 PriorityLevel_lowest = 14;
const OSS_UINT32 no_priority = 15;

const OSS_UINT32 rab_pre_empted = 1;
const OSS_UINT32 trelocoverall_expiry = 2;
const OSS_UINT32 trelocprep_expiry = 3;
const OSS_UINT32 treloccomplete_expiry = 4;
const OSS_UINT32 tqueing_expiry = 5;
const OSS_UINT32 relocation_triggered = 6;
const OSS_UINT32 trellocalloc_expiry = 7;
const OSS_UINT32 unable_to_establish_during_relocation = 8;
const OSS_UINT32 unknown_target_rnc = 9;
const OSS_UINT32 relocation_cancelled = 10;
const OSS_UINT32 successful_relocation = 11;
const OSS_UINT32 requested_ciphering_and_or_integrity_protection_algorithms_not_supported = 12;
const OSS_UINT32 conflict_with_already_existing_integrity_protection_and_or_ciphering_information = 13;
const OSS_UINT32 failure_in_the_radio_interface_procedure = 14;
const OSS_UINT32 release_due_to_utran_generated_reason = 15;
const OSS_UINT32 user_inactivity = 16;
const OSS_UINT32 time_critical_relocation = 17;
const OSS_UINT32 requested_traffic_class_not_available = 18;
const OSS_UINT32 invalid_rab_parameters_value = 19;
const OSS_UINT32 requested_maximum_bit_rate_not_available = 20;
const OSS_UINT32 requested_guaranteed_bit_rate_not_available = 21;
const OSS_UINT32 requested_transfer_delay_not_achievable = 22;
const OSS_UINT32 invalid_rab_parameters_combination = 23;
const OSS_UINT32 condition_violation_for_sdu_parameters = 24;
const OSS_UINT32 condition_violation_for_traffic_handling_priority = 25;
const OSS_UINT32 condition_violation_for_guaranteed_bit_rate = 26;
const OSS_UINT32 user_plane_versions_not_supported = 27;
const OSS_UINT32 iu_up_failure = 28;
const OSS_UINT32 relocation_failure_in_target_CN_RNC_or_target_system = 29;
const OSS_UINT32 invalid_RAB_ID = 30;
const OSS_UINT32 no_remaining_rab = 31;
const OSS_UINT32 interaction_with_other_procedure = 32;
const OSS_UINT32 requested_maximum_bit_rate_for_dl_not_available = 33;
const OSS_UINT32 requested_maximum_bit_rate_for_ul_not_available = 34;
const OSS_UINT32 requested_guaranteed_bit_rate_for_dl_not_available = 35;
const OSS_UINT32 requested_guaranteed_bit_rate_for_ul_not_available = 36;
const OSS_UINT32 repeated_integrity_checking_failure = 37;
const OSS_UINT32 requested_request_type_not_supported = 38;
const OSS_UINT32 request_superseded = 39;
const OSS_UINT32 release_due_to_UE_generated_signalling_connection_release = 40;
const OSS_UINT32 resource_optimisation_relocation = 41;
const OSS_UINT32 requested_information_not_available = 42;
const OSS_UINT32 relocation_desirable_for_radio_reasons = 43;
const OSS_UINT32 relocation_not_supported_in_target_RNC_or_target_system = 44;
const OSS_UINT32 directed_retry = 45;
const OSS_UINT32 radio_connection_with_UE_Lost = 46;
const OSS_UINT32 rNC_unable_to_establish_all_RFCs = 47;
const OSS_UINT32 deciphering_keys_not_available = 48;
const OSS_UINT32 dedicated_assistance_data_not_available = 49;
const OSS_UINT32 relocation_target_not_allowed = 50;
const OSS_UINT32 location_reporting_congestion = 51;
const OSS_UINT32 reduce_load_in_serving_cell = 52;
const OSS_UINT32 no_radio_resources_available_in_target_cell = 53;
const OSS_UINT32 gERAN_Iumode_failure = 54;
const OSS_UINT32 access_restricted_due_to_shared_networks = 55;
const OSS_UINT32 incoming_relocation_not_supported_due_to_PUESBINE_feature = 56;

const OSS_UINT32 signalling_transport_resource_failure = 65;
const OSS_UINT32 iu_transport_connection_failed_to_establish = 66;

const OSS_UINT32 user_restriction_start_indication = 81;
const OSS_UINT32 user_restriction_end_indication = 82;
const OSS_UINT32 normal_release = 83;

const OSS_UINT32 transfer_syntax_error = 97;
const OSS_UINT32 semantic_error = 98;
const OSS_UINT32 message_not_compatible_with_receiver_state = 99;
const OSS_UINT32 abstract_syntax_error_reject = 100;
const OSS_UINT32 abstract_syntax_error_ignore_and_notify = 101;
const OSS_UINT32 abstract_syntax_error_falsely_constructed_message = 102;

const OSS_UINT32 om_intervention = 113;
const OSS_UINT32 no_resource_available = 114;
const OSS_UINT32 unspecified_failure = 115;
const OSS_UINT32 network_optimisation = 116;

const OSS_UINT32 TrafficHandlingPriority_spare = 0;
const OSS_UINT32 TrafficHandlingPriority_highest = 1;
const OSS_UINT32 TrafficHandlingPriority_lowest = 14;
const OSS_UINT32 no_priority_used = 15;
typedef OSS_UINT32 ProcedureCode;

class OSS_PUBLIC __shared1;

class OSS_PUBLIC __shared2 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared1 component;

    __shared2();
    __shared2(const __shared2 &);
    ~__shared2();

    __shared2 & operator = (const __shared2 &);
    int operator == (const __shared2 &) const;
    int operator != (const __shared2 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared2 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared2 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared2 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared3;

class OSS_PUBLIC __shared4 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared3 component;

    __shared4();
    __shared4(const __shared4 &);
    ~__shared4();

    __shared4 & operator = (const __shared4 &);
    int operator == (const __shared4 &) const;
    int operator != (const __shared4 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared4 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared4 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared4 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared5   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared2 protocolIEs;
    typedef __shared4 protocolExtensions;

    __shared5();
    __shared5(const __shared5 &);
    __shared5(const protocolIEs &, const protocolExtensions &);
    __shared5(const protocolIEs &);

    __shared5 & operator = (const __shared5 &);
    int operator == (const __shared5 &) const;
    int operator != (const __shared5 &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

typedef __shared5 Iu_ReleaseCommand;

class OSS_PUBLIC __seq70;

class OSS_PUBLIC __seqof62 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq70 component;

    __seqof62();
    __seqof62(const __seqof62 &);
    ~__seqof62();

    __seqof62 & operator = (const __seqof62 &);
    int operator == (const __seqof62 &) const;
    int operator != (const __seqof62 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof62 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof62 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof62 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared7;

class OSS_PUBLIC __shared8 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared7 component;

    __shared8();
    __shared8(const __shared8 &);
    ~__shared8();

    __shared8 & operator = (const __shared8 &);
    int operator == (const __shared8 &) const;
    int operator != (const __shared8 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared8 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared8 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared8 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationRequired   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof62 protocolIEs;
    typedef __shared8 protocolExtensions;

    RelocationRequired();
    RelocationRequired(const RelocationRequired &);
    RelocationRequired(const protocolIEs &, const protocolExtensions &);
    RelocationRequired(const protocolIEs &);

    RelocationRequired & operator = (const RelocationRequired &);
    int operator == (const RelocationRequired &) const;
    int operator != (const RelocationRequired &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq80;

class OSS_PUBLIC __seqof72 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq80 component;

    __seqof72();
    __seqof72(const __seqof72 &);
    ~__seqof72();

    __seqof72 & operator = (const __seqof72 &);
    int operator == (const __seqof72 &) const;
    int operator != (const __seqof72 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof72 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof72 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof72 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq81;

class OSS_PUBLIC __seqof73 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq81 component;

    __seqof73();
    __seqof73(const __seqof73 &);
    ~__seqof73();

    __seqof73 & operator = (const __seqof73 &);
    int operator == (const __seqof73 &) const;
    int operator != (const __seqof73 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof73 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof73 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof73 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof72 protocolIEs;
    typedef __seqof73 protocolExtensions;

    RelocationRequest();
    RelocationRequest(const RelocationRequest &);
    RelocationRequest(const protocolIEs &, const protocolExtensions &);
    RelocationRequest(const protocolIEs &);

    RelocationRequest & operator = (const RelocationRequest &);
    int operator == (const RelocationRequest &) const;
    int operator != (const RelocationRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

typedef __shared5 RelocationCancel;

class OSS_PUBLIC __seq97;

class OSS_PUBLIC __seqof89 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq97 component;

    __seqof89();
    __seqof89(const __seqof89 &);
    ~__seqof89();

    __seqof89 & operator = (const __seqof89 &);
    int operator == (const __seqof89 &) const;
    int operator != (const __seqof89 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof89 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof89 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof89 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SRNS_ContextRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof89 protocolIEs;
    typedef __shared4 protocolExtensions;

    SRNS_ContextRequest();
    SRNS_ContextRequest(const SRNS_ContextRequest &);
    SRNS_ContextRequest(const protocolIEs &, const protocolExtensions &);
    SRNS_ContextRequest(const protocolIEs &);

    SRNS_ContextRequest & operator = (const SRNS_ContextRequest &);
    int operator == (const SRNS_ContextRequest &) const;
    int operator != (const SRNS_ContextRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq107;

class OSS_PUBLIC __seqof99 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq107 component;

    __seqof99();
    __seqof99(const __seqof99 &);
    ~__seqof99();

    __seqof99 & operator = (const __seqof99 &);
    int operator == (const __seqof99 &) const;
    int operator != (const __seqof99 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof99 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof99 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof99 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SecurityModeCommand   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof99 protocolIEs;
    typedef __shared4 protocolExtensions;

    SecurityModeCommand();
    SecurityModeCommand(const SecurityModeCommand &);
    SecurityModeCommand(const protocolIEs &, const protocolExtensions &);
    SecurityModeCommand(const protocolIEs &);

    SecurityModeCommand & operator = (const SecurityModeCommand &);
    int operator == (const SecurityModeCommand &) const;
    int operator != (const SecurityModeCommand &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq113;

class OSS_PUBLIC __seqof105 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq113 component;

    __seqof105();
    __seqof105(const __seqof105 &);
    ~__seqof105();

    __seqof105 & operator = (const __seqof105 &);
    int operator == (const __seqof105 &) const;
    int operator != (const __seqof105 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof105 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof105 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof105 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DataVolumeReportRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof105 protocolIEs;
    typedef __shared4 protocolExtensions;

    DataVolumeReportRequest();
    DataVolumeReportRequest(const DataVolumeReportRequest &);
    DataVolumeReportRequest(const protocolIEs &, const protocolExtensions &);
    DataVolumeReportRequest(const protocolIEs &);

    DataVolumeReportRequest & operator = (const DataVolumeReportRequest &);
    int operator == (const DataVolumeReportRequest &) const;
    int operator != (const DataVolumeReportRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq121;

class OSS_PUBLIC __seqof113 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq121 component;

    __seqof113();
    __seqof113(const __seqof113 &);
    ~__seqof113();

    __seqof113 & operator = (const __seqof113 &);
    int operator == (const __seqof113 &) const;
    int operator != (const __seqof113 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof113 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof113 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof113 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared17;

class OSS_PUBLIC __shared18 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared17 component;

    __shared18();
    __shared18(const __shared18 &);
    ~__shared18();

    __shared18 & operator = (const __shared18 &);
    int operator == (const __shared18 &) const;
    int operator != (const __shared18 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared18 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared18 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared18 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC Reset   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof113 protocolIEs;
    typedef __shared18 protocolExtensions;

    Reset();
    Reset(const Reset &);
    Reset(const protocolIEs &, const protocolExtensions &);
    Reset(const protocolIEs &);

    Reset & operator = (const Reset &);
    int operator == (const Reset &) const;
    int operator != (const Reset &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq125;

class OSS_PUBLIC __seqof117 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq125 component;

    __seqof117();
    __seqof117(const __seqof117 &);
    ~__seqof117();

    __seqof117 & operator = (const __seqof117 &);
    int operator == (const __seqof117 &) const;
    int operator != (const __seqof117 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof117 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof117 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof117 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ResetResource   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof117 protocolIEs;
    typedef __shared18 protocolExtensions;

    ResetResource();
    ResetResource(const ResetResource &);
    ResetResource(const protocolIEs &, const protocolExtensions &);
    ResetResource(const protocolIEs &);

    ResetResource & operator = (const ResetResource &);
    int operator == (const ResetResource &) const;
    int operator != (const ResetResource &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq133;

class OSS_PUBLIC __seqof125 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq133 component;

    __seqof125();
    __seqof125(const __seqof125 &);
    ~__seqof125();

    __seqof125 & operator = (const __seqof125 &);
    int operator == (const __seqof125 &) const;
    int operator != (const __seqof125 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof125 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof125 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof125 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_ReleaseRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof125 protocolIEs;
    typedef __shared4 protocolExtensions;

    RAB_ReleaseRequest();
    RAB_ReleaseRequest(const RAB_ReleaseRequest &);
    RAB_ReleaseRequest(const protocolIEs &, const protocolExtensions &);
    RAB_ReleaseRequest(const protocolIEs &);

    RAB_ReleaseRequest & operator = (const RAB_ReleaseRequest &);
    int operator == (const RAB_ReleaseRequest &) const;
    int operator != (const RAB_ReleaseRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

typedef __shared5 Iu_ReleaseRequest;

class OSS_PUBLIC __shared21;

class OSS_PUBLIC __shared22 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared21 component;

    __shared22();
    __shared22(const __shared22 &);
    ~__shared22();

    __shared22 & operator = (const __shared22 &);
    int operator == (const __shared22 &) const;
    int operator != (const __shared22 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared22 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared22 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared22 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared23   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared22 protocolIEs;
    typedef __shared4 protocolExtensions;

    __shared23();
    __shared23(const __shared23 &);
    __shared23(const protocolIEs &, const protocolExtensions &);
    __shared23(const protocolIEs &);

    __shared23 & operator = (const __shared23 &);
    int operator == (const __shared23 &) const;
    int operator != (const __shared23 &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

typedef __shared23 RelocationDetect;

typedef __shared23 RelocationComplete;

class OSS_PUBLIC __seq143;

class OSS_PUBLIC __seqof135 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq143 component;

    __seqof135();
    __seqof135(const __seqof135 &);
    ~__seqof135();

    __seqof135 & operator = (const __seqof135 &);
    int operator == (const __seqof135 &) const;
    int operator != (const __seqof135 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof135 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof135 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof135 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC Paging   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof135 protocolIEs;
    typedef __shared18 protocolExtensions;

    Paging();
    Paging(const Paging &);
    Paging(const protocolIEs &, const protocolExtensions &);
    Paging(const protocolIEs &);

    Paging & operator = (const Paging &);
    int operator == (const Paging &) const;
    int operator != (const Paging &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq145;

class OSS_PUBLIC __seqof137 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq145 component;

    __seqof137();
    __seqof137(const __seqof137 &);
    ~__seqof137();

    __seqof137 & operator = (const __seqof137 &);
    int operator == (const __seqof137 &) const;
    int operator != (const __seqof137 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof137 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof137 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof137 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq146;

class OSS_PUBLIC __seqof138 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq146 component;

    __seqof138();
    __seqof138(const __seqof138 &);
    ~__seqof138();

    __seqof138 & operator = (const __seqof138 &);
    int operator == (const __seqof138 &) const;
    int operator != (const __seqof138 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof138 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof138 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof138 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC CommonID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof137 protocolIEs;
    typedef __seqof138 protocolExtensions;

    CommonID();
    CommonID(const CommonID &);
    CommonID(const protocolIEs &, const protocolExtensions &);
    CommonID(const protocolIEs &);

    CommonID & operator = (const CommonID &);
    int operator == (const CommonID &) const;
    int operator != (const CommonID &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq147;

class OSS_PUBLIC __seqof139 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq147 component;

    __seqof139();
    __seqof139(const __seqof139 &);
    ~__seqof139();

    __seqof139 & operator = (const __seqof139 &);
    int operator == (const __seqof139 &) const;
    int operator != (const __seqof139 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof139 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof139 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof139 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq148;

class OSS_PUBLIC __seqof140 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq148 component;

    __seqof140();
    __seqof140(const __seqof140 &);
    ~__seqof140();

    __seqof140 & operator = (const __seqof140 &);
    int operator == (const __seqof140 &) const;
    int operator != (const __seqof140 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof140 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof140 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof140 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC CN_InvokeTrace   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof139 protocolIEs;
    typedef __seqof140 protocolExtensions;

    CN_InvokeTrace();
    CN_InvokeTrace(const CN_InvokeTrace &);
    CN_InvokeTrace(const protocolIEs &, const protocolExtensions &);
    CN_InvokeTrace(const protocolIEs &);

    CN_InvokeTrace & operator = (const CN_InvokeTrace &);
    int operator == (const CN_InvokeTrace &) const;
    int operator != (const CN_InvokeTrace &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq149;

class OSS_PUBLIC __seqof141 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq149 component;

    __seqof141();
    __seqof141(const __seqof141 &);
    ~__seqof141();

    __seqof141 & operator = (const __seqof141 &);
    int operator == (const __seqof141 &) const;
    int operator != (const __seqof141 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof141 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof141 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof141 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC CN_DeactivateTrace   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof141 protocolIEs;
    typedef __shared4 protocolExtensions;

    CN_DeactivateTrace();
    CN_DeactivateTrace(const CN_DeactivateTrace &);
    CN_DeactivateTrace(const protocolIEs &, const protocolExtensions &);
    CN_DeactivateTrace(const protocolIEs &);

    CN_DeactivateTrace & operator = (const CN_DeactivateTrace &);
    int operator == (const CN_DeactivateTrace &) const;
    int operator != (const CN_DeactivateTrace &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq151;

class OSS_PUBLIC __seqof143 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq151 component;

    __seqof143();
    __seqof143(const __seqof143 &);
    ~__seqof143();

    __seqof143 & operator = (const __seqof143 &);
    int operator == (const __seqof143 &) const;
    int operator != (const __seqof143 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof143 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof143 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof143 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq152;

class OSS_PUBLIC __seqof144 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq152 component;

    __seqof144();
    __seqof144(const __seqof144 &);
    ~__seqof144();

    __seqof144 & operator = (const __seqof144 &);
    int operator == (const __seqof144 &) const;
    int operator != (const __seqof144 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof144 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof144 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof144 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC LocationReportingControl   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof143 protocolIEs;
    typedef __seqof144 protocolExtensions;

    LocationReportingControl();
    LocationReportingControl(const LocationReportingControl &);
    LocationReportingControl(const protocolIEs &, const protocolExtensions &);
    LocationReportingControl(const protocolIEs &);

    LocationReportingControl & operator = (const LocationReportingControl &);
    int operator == (const LocationReportingControl &) const;
    int operator != (const LocationReportingControl &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq153;

class OSS_PUBLIC __seqof145 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq153 component;

    __seqof145();
    __seqof145(const __seqof145 &);
    ~__seqof145();

    __seqof145 & operator = (const __seqof145 &);
    int operator == (const __seqof145 &) const;
    int operator != (const __seqof145 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof145 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof145 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof145 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq154;

class OSS_PUBLIC __seqof146 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq154 component;

    __seqof146();
    __seqof146(const __seqof146 &);
    ~__seqof146();

    __seqof146 & operator = (const __seqof146 &);
    int operator == (const __seqof146 &) const;
    int operator != (const __seqof146 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof146 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof146 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof146 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC LocationReport   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof145 protocolIEs;
    typedef __seqof146 protocolExtensions;

    LocationReport();
    LocationReport(const LocationReport &);
    LocationReport(const protocolIEs &, const protocolExtensions &);
    LocationReport(const protocolIEs &);

    LocationReport & operator = (const LocationReport &);
    int operator == (const LocationReport &) const;
    int operator != (const LocationReport &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq155;

class OSS_PUBLIC __seqof147 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq155 component;

    __seqof147();
    __seqof147(const __seqof147 &);
    ~__seqof147();

    __seqof147 & operator = (const __seqof147 &);
    int operator == (const __seqof147 &) const;
    int operator != (const __seqof147 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof147 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof147 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof147 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC InitialUE_Message   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof147 protocolIEs;
    typedef __shared8 protocolExtensions;

    InitialUE_Message();
    InitialUE_Message(const InitialUE_Message &);
    InitialUE_Message(const protocolIEs &, const protocolExtensions &);
    InitialUE_Message(const protocolIEs &);

    InitialUE_Message & operator = (const InitialUE_Message &);
    int operator == (const InitialUE_Message &) const;
    int operator != (const InitialUE_Message &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq157;

class OSS_PUBLIC __seqof149 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq157 component;

    __seqof149();
    __seqof149(const __seqof149 &);
    ~__seqof149();

    __seqof149 & operator = (const __seqof149 &);
    int operator == (const __seqof149 &) const;
    int operator != (const __seqof149 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof149 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof149 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof149 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DirectTransfer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof149 protocolIEs;
    typedef __shared4 protocolExtensions;

    DirectTransfer();
    DirectTransfer(const DirectTransfer &);
    DirectTransfer(const protocolIEs &, const protocolExtensions &);
    DirectTransfer(const protocolIEs &);

    DirectTransfer & operator = (const DirectTransfer &);
    int operator == (const DirectTransfer &) const;
    int operator != (const DirectTransfer &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq159;

class OSS_PUBLIC __seqof151 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq159 component;

    __seqof151();
    __seqof151(const __seqof151 &);
    ~__seqof151();

    __seqof151 & operator = (const __seqof151 &);
    int operator == (const __seqof151 &) const;
    int operator != (const __seqof151 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof151 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof151 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof151 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq160;

class OSS_PUBLIC __seqof152 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq160 component;

    __seqof152();
    __seqof152(const __seqof152 &);
    ~__seqof152();

    __seqof152 & operator = (const __seqof152 &);
    int operator == (const __seqof152 &) const;
    int operator != (const __seqof152 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof152 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof152 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof152 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC Overload   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof151 protocolIEs;
    typedef __seqof152 protocolExtensions;

    Overload();
    Overload(const Overload &);
    Overload(const protocolIEs &, const protocolExtensions &);
    Overload(const protocolIEs &);

    Overload & operator = (const Overload &);
    int operator == (const Overload &) const;
    int operator != (const Overload &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq161;

class OSS_PUBLIC __seqof153 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq161 component;

    __seqof153();
    __seqof153(const __seqof153 &);
    ~__seqof153();

    __seqof153 & operator = (const __seqof153 &);
    int operator == (const __seqof153 &) const;
    int operator != (const __seqof153 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof153 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof153 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof153 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ErrorIndication   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof153 protocolIEs;
    typedef __shared18 protocolExtensions;

    ErrorIndication();
    ErrorIndication(const ErrorIndication &);
    ErrorIndication(const protocolIEs &, const protocolExtensions &);
    ErrorIndication(const protocolIEs &);

    ErrorIndication & operator = (const ErrorIndication &);
    int operator == (const ErrorIndication &) const;
    int operator != (const ErrorIndication &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq163;

class OSS_PUBLIC __seqof155 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq163 component;

    __seqof155();
    __seqof155(const __seqof155 &);
    ~__seqof155();

    __seqof155 & operator = (const __seqof155 &);
    int operator == (const __seqof155 &) const;
    int operator != (const __seqof155 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof155 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof155 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof155 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SRNS_DataForwardCommand   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof155 protocolIEs;
    typedef __shared4 protocolExtensions;

    SRNS_DataForwardCommand();
    SRNS_DataForwardCommand(const SRNS_DataForwardCommand &);
    SRNS_DataForwardCommand(const protocolIEs &, const protocolExtensions &);
    SRNS_DataForwardCommand(const protocolIEs &);

    SRNS_DataForwardCommand & operator = (const SRNS_DataForwardCommand &);
    int operator == (const SRNS_DataForwardCommand &) const;
    int operator != (const SRNS_DataForwardCommand &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq165;

class OSS_PUBLIC __seqof157 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq165 component;

    __seqof157();
    __seqof157(const __seqof157 &);
    ~__seqof157();

    __seqof157 & operator = (const __seqof157 &);
    int operator == (const __seqof157 &) const;
    int operator != (const __seqof157 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof157 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof157 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof157 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared29;

class OSS_PUBLIC __shared30 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared29 component;

    __shared30();
    __shared30(const __shared30 &);
    ~__shared30();

    __shared30 & operator = (const __shared30 &);
    int operator == (const __shared30 &) const;
    int operator != (const __shared30 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared30 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared30 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared30 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ForwardSRNS_Context   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof157 protocolIEs;
    typedef __shared30 protocolExtensions;

    ForwardSRNS_Context();
    ForwardSRNS_Context(const ForwardSRNS_Context &);
    ForwardSRNS_Context(const protocolIEs &, const protocolExtensions &);
    ForwardSRNS_Context(const protocolIEs &);

    ForwardSRNS_Context & operator = (const ForwardSRNS_Context &);
    int operator == (const ForwardSRNS_Context &) const;
    int operator != (const ForwardSRNS_Context &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC PrivateIE_Field;

class OSS_PUBLIC __seqof176 : public OssList  /* SEQUENCE OF */
{
public:
    typedef PrivateIE_Field component;

    __seqof176();
    __seqof176(const __seqof176 &);
    ~__seqof176();

    __seqof176 & operator = (const __seqof176 &);
    int operator == (const __seqof176 &) const;
    int operator != (const __seqof176 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof176 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof176 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof176 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC PrivateMessage   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof176 privateIEs;

    PrivateMessage();
    PrivateMessage(const PrivateMessage &);
    PrivateMessage(const privateIEs &);

    PrivateMessage & operator = (const PrivateMessage &);
    int operator == (const PrivateMessage &) const;
    int operator != (const PrivateMessage &) const;

    privateIEs & get_privateIEs();
    const privateIEs & get_privateIEs() const;
    void set_privateIEs(const privateIEs &);
private:
    privateIEs privateIEs_field;
};

class OSS_PUBLIC __seq184;

class OSS_PUBLIC __seqof177 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq184 component;

    __seqof177();
    __seqof177(const __seqof177 &);
    ~__seqof177();

    __seqof177 & operator = (const __seqof177 &);
    int operator == (const __seqof177 &) const;
    int operator != (const __seqof177 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof177 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof177 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof177 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RANAP_RelocationInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof177 protocolIEs;
    typedef __shared30 protocolExtensions;

    RANAP_RelocationInformation();
    RANAP_RelocationInformation(const RANAP_RelocationInformation &);
    RANAP_RelocationInformation(const protocolIEs &, const protocolExtensions &);
    RANAP_RelocationInformation(const protocolIEs &);

    RANAP_RelocationInformation & operator = (const RANAP_RelocationInformation &);
    int operator == (const RANAP_RelocationInformation &) const;
    int operator != (const RANAP_RelocationInformation &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq167;

class OSS_PUBLIC __seqof159 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq167 component;

    __seqof159();
    __seqof159(const __seqof159 &);
    ~__seqof159();

    __seqof159 & operator = (const __seqof159 &);
    int operator == (const __seqof159 &) const;
    int operator != (const __seqof159 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof159 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof159 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof159 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_AssignmentRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof159 protocolIEs;
    typedef __shared4 protocolExtensions;

    RAB_AssignmentRequest();
    RAB_AssignmentRequest(const RAB_AssignmentRequest &);
    RAB_AssignmentRequest(const protocolIEs &, const protocolExtensions &);
    RAB_AssignmentRequest(const protocolIEs &);

    RAB_AssignmentRequest & operator = (const RAB_AssignmentRequest &);
    int operator == (const RAB_AssignmentRequest &) const;
    int operator != (const RAB_AssignmentRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage : public OssConstrainedOpenType
{
public:
    RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage();
    RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage(const RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage &);
    ~RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage();
    RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage & operator = (const RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage &);
    int operator == (const RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage &) const;
    int operator != (const RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared5 *get_Iu_ReleaseCommand();
    const __shared5 *get_Iu_ReleaseCommand() const;
    void set_Iu_ReleaseCommand(const __shared5 &);
    __shared5 *release_Iu_ReleaseCommand();
    void set_Iu_ReleaseCommand(__shared5 *);

    RelocationRequired *get_RelocationRequired();
    const RelocationRequired *get_RelocationRequired() const;
    void set_RelocationRequired(const RelocationRequired &);
    RelocationRequired *release_RelocationRequired();
    void set_RelocationRequired(RelocationRequired *);

    RelocationRequest *get_RelocationRequest();
    const RelocationRequest *get_RelocationRequest() const;
    void set_RelocationRequest(const RelocationRequest &);
    RelocationRequest *release_RelocationRequest();
    void set_RelocationRequest(RelocationRequest *);

    __shared5 *get_RelocationCancel();
    const __shared5 *get_RelocationCancel() const;
    void set_RelocationCancel(const __shared5 &);
    __shared5 *release_RelocationCancel();
    void set_RelocationCancel(__shared5 *);

    SRNS_ContextRequest *get_SRNS_ContextRequest();
    const SRNS_ContextRequest *get_SRNS_ContextRequest() const;
    void set_SRNS_ContextRequest(const SRNS_ContextRequest &);
    SRNS_ContextRequest *release_SRNS_ContextRequest();
    void set_SRNS_ContextRequest(SRNS_ContextRequest *);

    SecurityModeCommand *get_SecurityModeCommand();
    const SecurityModeCommand *get_SecurityModeCommand() const;
    void set_SecurityModeCommand(const SecurityModeCommand &);
    SecurityModeCommand *release_SecurityModeCommand();
    void set_SecurityModeCommand(SecurityModeCommand *);

    DataVolumeReportRequest *get_DataVolumeReportRequest();
    const DataVolumeReportRequest *get_DataVolumeReportRequest() const;
    void set_DataVolumeReportRequest(const DataVolumeReportRequest &);
    DataVolumeReportRequest *release_DataVolumeReportRequest();
    void set_DataVolumeReportRequest(DataVolumeReportRequest *);

    Reset *get_Reset();
    const Reset *get_Reset() const;
    void set_Reset(const Reset &);
    Reset *release_Reset();
    void set_Reset(Reset *);

    ResetResource *get_ResetResource();
    const ResetResource *get_ResetResource() const;
    void set_ResetResource(const ResetResource &);
    ResetResource *release_ResetResource();
    void set_ResetResource(ResetResource *);

    RAB_ReleaseRequest *get_RAB_ReleaseRequest();
    const RAB_ReleaseRequest *get_RAB_ReleaseRequest() const;
    void set_RAB_ReleaseRequest(const RAB_ReleaseRequest &);
    RAB_ReleaseRequest *release_RAB_ReleaseRequest();
    void set_RAB_ReleaseRequest(RAB_ReleaseRequest *);

    __shared5 *get_Iu_ReleaseRequest();
    const __shared5 *get_Iu_ReleaseRequest() const;
    void set_Iu_ReleaseRequest(const __shared5 &);
    __shared5 *release_Iu_ReleaseRequest();
    void set_Iu_ReleaseRequest(__shared5 *);

    __shared23 *get_RelocationDetect();
    const __shared23 *get_RelocationDetect() const;
    void set_RelocationDetect(const __shared23 &);
    __shared23 *release_RelocationDetect();
    void set_RelocationDetect(__shared23 *);

    __shared23 *get_RelocationComplete();
    const __shared23 *get_RelocationComplete() const;
    void set_RelocationComplete(const __shared23 &);
    __shared23 *release_RelocationComplete();
    void set_RelocationComplete(__shared23 *);

    Paging *get_Paging();
    const Paging *get_Paging() const;
    void set_Paging(const Paging &);
    Paging *release_Paging();
    void set_Paging(Paging *);

    CommonID *get_CommonID();
    const CommonID *get_CommonID() const;
    void set_CommonID(const CommonID &);
    CommonID *release_CommonID();
    void set_CommonID(CommonID *);

    CN_InvokeTrace *get_CN_InvokeTrace();
    const CN_InvokeTrace *get_CN_InvokeTrace() const;
    void set_CN_InvokeTrace(const CN_InvokeTrace &);
    CN_InvokeTrace *release_CN_InvokeTrace();
    void set_CN_InvokeTrace(CN_InvokeTrace *);

    CN_DeactivateTrace *get_CN_DeactivateTrace();
    const CN_DeactivateTrace *get_CN_DeactivateTrace() const;
    void set_CN_DeactivateTrace(const CN_DeactivateTrace &);
    CN_DeactivateTrace *release_CN_DeactivateTrace();
    void set_CN_DeactivateTrace(CN_DeactivateTrace *);

    LocationReportingControl *get_LocationReportingControl();
    const LocationReportingControl *get_LocationReportingControl() const;
    void set_LocationReportingControl(const LocationReportingControl &);
    LocationReportingControl *release_LocationReportingControl();
    void set_LocationReportingControl(LocationReportingControl *);

    LocationReport *get_LocationReport();
    const LocationReport *get_LocationReport() const;
    void set_LocationReport(const LocationReport &);
    LocationReport *release_LocationReport();
    void set_LocationReport(LocationReport *);

    InitialUE_Message *get_InitialUE_Message();
    const InitialUE_Message *get_InitialUE_Message() const;
    void set_InitialUE_Message(const InitialUE_Message &);
    InitialUE_Message *release_InitialUE_Message();
    void set_InitialUE_Message(InitialUE_Message *);

    DirectTransfer *get_DirectTransfer();
    const DirectTransfer *get_DirectTransfer() const;
    void set_DirectTransfer(const DirectTransfer &);
    DirectTransfer *release_DirectTransfer();
    void set_DirectTransfer(DirectTransfer *);

    Overload *get_Overload();
    const Overload *get_Overload() const;
    void set_Overload(const Overload &);
    Overload *release_Overload();
    void set_Overload(Overload *);

    ErrorIndication *get_ErrorIndication();
    const ErrorIndication *get_ErrorIndication() const;
    void set_ErrorIndication(const ErrorIndication &);
    ErrorIndication *release_ErrorIndication();
    void set_ErrorIndication(ErrorIndication *);

    SRNS_DataForwardCommand *get_SRNS_DataForwardCommand();
    const SRNS_DataForwardCommand *get_SRNS_DataForwardCommand() const;
    void set_SRNS_DataForwardCommand(const SRNS_DataForwardCommand &);
    SRNS_DataForwardCommand *release_SRNS_DataForwardCommand();
    void set_SRNS_DataForwardCommand(SRNS_DataForwardCommand *);

    ForwardSRNS_Context *get_ForwardSRNS_Context();
    const ForwardSRNS_Context *get_ForwardSRNS_Context() const;
    void set_ForwardSRNS_Context(const ForwardSRNS_Context &);
    ForwardSRNS_Context *release_ForwardSRNS_Context();
    void set_ForwardSRNS_Context(ForwardSRNS_Context *);

    PrivateMessage *get_PrivateMessage();
    const PrivateMessage *get_PrivateMessage() const;
    void set_PrivateMessage(const PrivateMessage &);
    PrivateMessage *release_PrivateMessage();
    void set_PrivateMessage(PrivateMessage *);

    RANAP_RelocationInformation *get_RANAP_RelocationInformation();
    const RANAP_RelocationInformation *get_RANAP_RelocationInformation() const;
    void set_RANAP_RelocationInformation(const RANAP_RelocationInformation &);
    RANAP_RelocationInformation *release_RANAP_RelocationInformation();
    void set_RANAP_RelocationInformation(RANAP_RelocationInformation *);

    RAB_AssignmentRequest *get_RAB_AssignmentRequest();
    const RAB_AssignmentRequest *get_RAB_AssignmentRequest() const;
    void set_RAB_AssignmentRequest(const RAB_AssignmentRequest &);
    RAB_AssignmentRequest *release_RAB_AssignmentRequest();
    void set_RAB_AssignmentRequest(RAB_AssignmentRequest *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC InitiatingMessage   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 procedureCode;
    typedef enum Criticality criticality;
    typedef RANAP_ELEMENTARY_PROCEDURES_InitiatingMessage value;

    InitiatingMessage();
    InitiatingMessage(const InitiatingMessage &);
    InitiatingMessage(procedureCode, criticality, const value &);

    InitiatingMessage & operator = (const InitiatingMessage &);
    int operator == (const InitiatingMessage &) const;
    int operator != (const InitiatingMessage &) const;

    procedureCode & get_procedureCode();
    procedureCode get_procedureCode() const;
    void set_procedureCode(procedureCode);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    procedureCode procedureCode_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq64;

class OSS_PUBLIC __seqof56 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq64 component;

    __seqof56();
    __seqof56(const __seqof56 &);
    ~__seqof56();

    __seqof56 & operator = (const __seqof56 &);
    int operator == (const __seqof56 &) const;
    int operator != (const __seqof56 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof56 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof56 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof56 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC Iu_ReleaseComplete   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof56 protocolIEs;
    typedef __shared4 protocolExtensions;

    Iu_ReleaseComplete();
    Iu_ReleaseComplete(const Iu_ReleaseComplete &);
    Iu_ReleaseComplete(const protocolIEs &, const protocolExtensions &);
    Iu_ReleaseComplete(const protocolIEs &);

    Iu_ReleaseComplete & operator = (const Iu_ReleaseComplete &);
    int operator == (const Iu_ReleaseComplete &) const;
    int operator != (const Iu_ReleaseComplete &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq72;

class OSS_PUBLIC __seqof64 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq72 component;

    __seqof64();
    __seqof64(const __seqof64 &);
    ~__seqof64();

    __seqof64 & operator = (const __seqof64 &);
    int operator == (const __seqof64 &) const;
    int operator != (const __seqof64 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof64 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof64 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof64 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared32;

class OSS_PUBLIC __shared33 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared32 component;

    __shared33();
    __shared33(const __shared33 &);
    ~__shared33();

    __shared33 & operator = (const __shared33 &);
    int operator == (const __shared33 &) const;
    int operator != (const __shared33 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared33 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared33 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared33 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationCommand   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof64 protocolIEs;
    typedef __shared33 protocolExtensions;

    RelocationCommand();
    RelocationCommand(const RelocationCommand &);
    RelocationCommand(const protocolIEs &, const protocolExtensions &);
    RelocationCommand(const protocolIEs &);

    RelocationCommand & operator = (const RelocationCommand &);
    int operator == (const RelocationCommand &) const;
    int operator != (const RelocationCommand &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq85;

class OSS_PUBLIC __seqof77 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq85 component;

    __seqof77();
    __seqof77(const __seqof77 &);
    ~__seqof77();

    __seqof77 & operator = (const __seqof77 &);
    int operator == (const __seqof77 &) const;
    int operator != (const __seqof77 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof77 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof77 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof77 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq86;

class OSS_PUBLIC __seqof78 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq86 component;

    __seqof78();
    __seqof78(const __seqof78 &);
    ~__seqof78();

    __seqof78 & operator = (const __seqof78 &);
    int operator == (const __seqof78 &) const;
    int operator != (const __seqof78 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof78 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof78 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof78 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationRequestAcknowledge   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof77 protocolIEs;
    typedef __seqof78 protocolExtensions;

    RelocationRequestAcknowledge();
    RelocationRequestAcknowledge(const RelocationRequestAcknowledge &);
    RelocationRequestAcknowledge(const protocolIEs &, const protocolExtensions &);
    RelocationRequestAcknowledge(const protocolIEs &);

    RelocationRequestAcknowledge & operator = (const RelocationRequestAcknowledge &);
    int operator == (const RelocationRequestAcknowledge &) const;
    int operator != (const RelocationRequestAcknowledge &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq95;

class OSS_PUBLIC __seqof87 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq95 component;

    __seqof87();
    __seqof87(const __seqof87 &);
    ~__seqof87();

    __seqof87 & operator = (const __seqof87 &);
    int operator == (const __seqof87 &) const;
    int operator != (const __seqof87 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof87 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof87 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof87 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationCancelAcknowledge   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof87 protocolIEs;
    typedef __shared4 protocolExtensions;

    RelocationCancelAcknowledge();
    RelocationCancelAcknowledge(const RelocationCancelAcknowledge &);
    RelocationCancelAcknowledge(const protocolIEs &, const protocolExtensions &);
    RelocationCancelAcknowledge(const protocolIEs &);

    RelocationCancelAcknowledge & operator = (const RelocationCancelAcknowledge &);
    int operator == (const RelocationCancelAcknowledge &) const;
    int operator != (const RelocationCancelAcknowledge &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq101;

class OSS_PUBLIC __seqof93 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq101 component;

    __seqof93();
    __seqof93(const __seqof93 &);
    ~__seqof93();

    __seqof93 & operator = (const __seqof93 &);
    int operator == (const __seqof93 &) const;
    int operator != (const __seqof93 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof93 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof93 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof93 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SRNS_ContextResponse   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof93 protocolIEs;
    typedef __shared4 protocolExtensions;

    SRNS_ContextResponse();
    SRNS_ContextResponse(const SRNS_ContextResponse &);
    SRNS_ContextResponse(const protocolIEs &, const protocolExtensions &);
    SRNS_ContextResponse(const protocolIEs &);

    SRNS_ContextResponse & operator = (const SRNS_ContextResponse &);
    int operator == (const SRNS_ContextResponse &) const;
    int operator != (const SRNS_ContextResponse &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq109;

class OSS_PUBLIC __seqof101 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq109 component;

    __seqof101();
    __seqof101(const __seqof101 &);
    ~__seqof101();

    __seqof101 & operator = (const __seqof101 &);
    int operator == (const __seqof101 &) const;
    int operator != (const __seqof101 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof101 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof101 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof101 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SecurityModeComplete   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof101 protocolIEs;
    typedef __shared4 protocolExtensions;

    SecurityModeComplete();
    SecurityModeComplete(const SecurityModeComplete &);
    SecurityModeComplete(const protocolIEs &, const protocolExtensions &);
    SecurityModeComplete(const protocolIEs &);

    SecurityModeComplete & operator = (const SecurityModeComplete &);
    int operator == (const SecurityModeComplete &) const;
    int operator != (const SecurityModeComplete &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq117;

class OSS_PUBLIC __seqof109 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq117 component;

    __seqof109();
    __seqof109(const __seqof109 &);
    ~__seqof109();

    __seqof109 & operator = (const __seqof109 &);
    int operator == (const __seqof109 &) const;
    int operator != (const __seqof109 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof109 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof109 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof109 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DataVolumeReport   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof109 protocolIEs;
    typedef __shared4 protocolExtensions;

    DataVolumeReport();
    DataVolumeReport(const DataVolumeReport &);
    DataVolumeReport(const protocolIEs &, const protocolExtensions &);
    DataVolumeReport(const protocolIEs &);

    DataVolumeReport & operator = (const DataVolumeReport &);
    int operator == (const DataVolumeReport &) const;
    int operator != (const DataVolumeReport &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq123;

class OSS_PUBLIC __seqof115 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq123 component;

    __seqof115();
    __seqof115(const __seqof115 &);
    ~__seqof115();

    __seqof115 & operator = (const __seqof115 &);
    int operator == (const __seqof115 &) const;
    int operator != (const __seqof115 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof115 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof115 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof115 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ResetAcknowledge   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof115 protocolIEs;
    typedef __shared18 protocolExtensions;

    ResetAcknowledge();
    ResetAcknowledge(const ResetAcknowledge &);
    ResetAcknowledge(const protocolIEs &, const protocolExtensions &);
    ResetAcknowledge(const protocolIEs &);

    ResetAcknowledge & operator = (const ResetAcknowledge &);
    int operator == (const ResetAcknowledge &) const;
    int operator != (const ResetAcknowledge &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq129;

class OSS_PUBLIC __seqof121 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq129 component;

    __seqof121();
    __seqof121(const __seqof121 &);
    ~__seqof121();

    __seqof121 & operator = (const __seqof121 &);
    int operator == (const __seqof121 &) const;
    int operator != (const __seqof121 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof121 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof121 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof121 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ResetResourceAcknowledge   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof121 protocolIEs;
    typedef __shared18 protocolExtensions;

    ResetResourceAcknowledge();
    ResetResourceAcknowledge(const ResetResourceAcknowledge &);
    ResetResourceAcknowledge(const protocolIEs &, const protocolExtensions &);
    ResetResourceAcknowledge(const protocolIEs &);

    ResetResourceAcknowledge & operator = (const ResetResourceAcknowledge &);
    int operator == (const ResetResourceAcknowledge &) const;
    int operator != (const ResetResourceAcknowledge &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome : public OssConstrainedOpenType
{
public:
    RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome();
    RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome(const RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome &);
    ~RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome();
    RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome & operator = (const RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome &);
    int operator == (const RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome &) const;
    int operator != (const RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Iu_ReleaseComplete *get_Iu_ReleaseComplete();
    const Iu_ReleaseComplete *get_Iu_ReleaseComplete() const;
    void set_Iu_ReleaseComplete(const Iu_ReleaseComplete &);
    Iu_ReleaseComplete *release_Iu_ReleaseComplete();
    void set_Iu_ReleaseComplete(Iu_ReleaseComplete *);

    RelocationCommand *get_RelocationCommand();
    const RelocationCommand *get_RelocationCommand() const;
    void set_RelocationCommand(const RelocationCommand &);
    RelocationCommand *release_RelocationCommand();
    void set_RelocationCommand(RelocationCommand *);

    RelocationRequestAcknowledge *get_RelocationRequestAcknowledge();
    const RelocationRequestAcknowledge *get_RelocationRequestAcknowledge() const;
    void set_RelocationRequestAcknowledge(const RelocationRequestAcknowledge &);
    RelocationRequestAcknowledge *release_RelocationRequestAcknowledge();
    void set_RelocationRequestAcknowledge(RelocationRequestAcknowledge *);

    RelocationCancelAcknowledge *get_RelocationCancelAcknowledge();
    const RelocationCancelAcknowledge *get_RelocationCancelAcknowledge() const;
    void set_RelocationCancelAcknowledge(const RelocationCancelAcknowledge &);
    RelocationCancelAcknowledge *release_RelocationCancelAcknowledge();
    void set_RelocationCancelAcknowledge(RelocationCancelAcknowledge *);

    SRNS_ContextResponse *get_SRNS_ContextResponse();
    const SRNS_ContextResponse *get_SRNS_ContextResponse() const;
    void set_SRNS_ContextResponse(const SRNS_ContextResponse &);
    SRNS_ContextResponse *release_SRNS_ContextResponse();
    void set_SRNS_ContextResponse(SRNS_ContextResponse *);

    SecurityModeComplete *get_SecurityModeComplete();
    const SecurityModeComplete *get_SecurityModeComplete() const;
    void set_SecurityModeComplete(const SecurityModeComplete &);
    SecurityModeComplete *release_SecurityModeComplete();
    void set_SecurityModeComplete(SecurityModeComplete *);

    DataVolumeReport *get_DataVolumeReport();
    const DataVolumeReport *get_DataVolumeReport() const;
    void set_DataVolumeReport(const DataVolumeReport &);
    DataVolumeReport *release_DataVolumeReport();
    void set_DataVolumeReport(DataVolumeReport *);

    ResetAcknowledge *get_ResetAcknowledge();
    const ResetAcknowledge *get_ResetAcknowledge() const;
    void set_ResetAcknowledge(const ResetAcknowledge &);
    ResetAcknowledge *release_ResetAcknowledge();
    void set_ResetAcknowledge(ResetAcknowledge *);

    ResetResourceAcknowledge *get_ResetResourceAcknowledge();
    const ResetResourceAcknowledge *get_ResetResourceAcknowledge() const;
    void set_ResetResourceAcknowledge(const ResetResourceAcknowledge &);
    ResetResourceAcknowledge *release_ResetResourceAcknowledge();
    void set_ResetResourceAcknowledge(ResetResourceAcknowledge *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC SuccessfulOutcome   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 procedureCode;
    typedef enum Criticality criticality;
    typedef RANAP_ELEMENTARY_PROCEDURES_SuccessfulOutcome value;

    SuccessfulOutcome();
    SuccessfulOutcome(const SuccessfulOutcome &);
    SuccessfulOutcome(procedureCode, criticality, const value &);

    SuccessfulOutcome & operator = (const SuccessfulOutcome &);
    int operator == (const SuccessfulOutcome &) const;
    int operator != (const SuccessfulOutcome &) const;

    procedureCode & get_procedureCode();
    procedureCode get_procedureCode() const;
    void set_procedureCode(procedureCode);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    procedureCode procedureCode_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared35;

class OSS_PUBLIC __shared36 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared35 component;

    __shared36();
    __shared36(const __shared36 &);
    ~__shared36();

    __shared36 & operator = (const __shared36 &);
    int operator == (const __shared36 &) const;
    int operator != (const __shared36 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared36 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared36 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared36 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationPreparationFailure   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared36 protocolIEs;
    typedef __shared33 protocolExtensions;

    RelocationPreparationFailure();
    RelocationPreparationFailure(const RelocationPreparationFailure &);
    RelocationPreparationFailure(const protocolIEs &, const protocolExtensions &);
    RelocationPreparationFailure(const protocolIEs &);

    RelocationPreparationFailure & operator = (const RelocationPreparationFailure &);
    int operator == (const RelocationPreparationFailure &) const;
    int operator != (const RelocationPreparationFailure &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq92;

class OSS_PUBLIC __seqof84 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq92 component;

    __seqof84();
    __seqof84(const __seqof84 &);
    ~__seqof84();

    __seqof84 & operator = (const __seqof84 &);
    int operator == (const __seqof84 &) const;
    int operator != (const __seqof84 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof84 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof84 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof84 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationFailure   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared36 protocolIEs;
    typedef __seqof84 protocolExtensions;

    RelocationFailure();
    RelocationFailure(const RelocationFailure &);
    RelocationFailure(const protocolIEs &, const protocolExtensions &);
    RelocationFailure(const protocolIEs &);

    RelocationFailure & operator = (const RelocationFailure &);
    int operator == (const RelocationFailure &) const;
    int operator != (const RelocationFailure &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC SecurityModeReject   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared36 protocolIEs;
    typedef __shared4 protocolExtensions;

    SecurityModeReject();
    SecurityModeReject(const SecurityModeReject &);
    SecurityModeReject(const protocolIEs &, const protocolExtensions &);
    SecurityModeReject(const protocolIEs &);

    SecurityModeReject & operator = (const SecurityModeReject &);
    int operator == (const SecurityModeReject &) const;
    int operator != (const SecurityModeReject &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome : public OssConstrainedOpenType
{
public:
    RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome();
    RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome(const RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome &);
    ~RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome();
    RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome & operator = (const RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome &);
    int operator == (const RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome &) const;
    int operator != (const RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RelocationPreparationFailure *get_RelocationPreparationFailure();
    const RelocationPreparationFailure *get_RelocationPreparationFailure() const;
    void set_RelocationPreparationFailure(const RelocationPreparationFailure &);
    RelocationPreparationFailure *release_RelocationPreparationFailure();
    void set_RelocationPreparationFailure(RelocationPreparationFailure *);

    RelocationFailure *get_RelocationFailure();
    const RelocationFailure *get_RelocationFailure() const;
    void set_RelocationFailure(const RelocationFailure &);
    RelocationFailure *release_RelocationFailure();
    void set_RelocationFailure(RelocationFailure *);

    SecurityModeReject *get_SecurityModeReject();
    const SecurityModeReject *get_SecurityModeReject() const;
    void set_SecurityModeReject(const SecurityModeReject &);
    SecurityModeReject *release_SecurityModeReject();
    void set_SecurityModeReject(SecurityModeReject *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC UnsuccessfulOutcome   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 procedureCode;
    typedef enum Criticality criticality;
    typedef RANAP_ELEMENTARY_PROCEDURES_UnsuccessfulOutcome value;

    UnsuccessfulOutcome();
    UnsuccessfulOutcome(const UnsuccessfulOutcome &);
    UnsuccessfulOutcome(procedureCode, criticality, const value &);

    UnsuccessfulOutcome & operator = (const UnsuccessfulOutcome &);
    int operator == (const UnsuccessfulOutcome &) const;
    int operator != (const UnsuccessfulOutcome &) const;

    procedureCode & get_procedureCode();
    procedureCode get_procedureCode() const;
    void set_procedureCode(procedureCode);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    procedureCode procedureCode_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq172;

class OSS_PUBLIC __seqof165 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq172 component;

    __seqof165();
    __seqof165(const __seqof165 &);
    ~__seqof165();

    __seqof165 & operator = (const __seqof165 &);
    int operator == (const __seqof165 &) const;
    int operator != (const __seqof165 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof165 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof165 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof165 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq173;

class OSS_PUBLIC __seqof166 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq173 component;

    __seqof166();
    __seqof166(const __seqof166 &);
    ~__seqof166();

    __seqof166 & operator = (const __seqof166 &);
    int operator == (const __seqof166 &) const;
    int operator != (const __seqof166 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof166 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof166 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof166 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_AssignmentResponse   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof165 protocolIEs;
    typedef __seqof166 protocolExtensions;

    RAB_AssignmentResponse();
    RAB_AssignmentResponse(const RAB_AssignmentResponse &);
    RAB_AssignmentResponse(const protocolIEs &, const protocolExtensions &);
    RAB_AssignmentResponse(const protocolIEs &);

    RAB_AssignmentResponse & operator = (const RAB_AssignmentResponse &);
    int operator == (const RAB_AssignmentResponse &) const;
    int operator != (const RAB_AssignmentResponse &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC RANAP_ELEMENTARY_PROCEDURES_Outcome : public OssConstrainedOpenType
{
public:
    RANAP_ELEMENTARY_PROCEDURES_Outcome();
    RANAP_ELEMENTARY_PROCEDURES_Outcome(const RANAP_ELEMENTARY_PROCEDURES_Outcome &);
    ~RANAP_ELEMENTARY_PROCEDURES_Outcome();
    RANAP_ELEMENTARY_PROCEDURES_Outcome & operator = (const RANAP_ELEMENTARY_PROCEDURES_Outcome &);
    int operator == (const RANAP_ELEMENTARY_PROCEDURES_Outcome &) const;
    int operator != (const RANAP_ELEMENTARY_PROCEDURES_Outcome &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_AssignmentResponse *get_RAB_AssignmentResponse();
    const RAB_AssignmentResponse *get_RAB_AssignmentResponse() const;
    void set_RAB_AssignmentResponse(const RAB_AssignmentResponse &);
    RAB_AssignmentResponse *release_RAB_AssignmentResponse();
    void set_RAB_AssignmentResponse(RAB_AssignmentResponse *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC Outcome   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 procedureCode;
    typedef enum Criticality criticality;
    typedef RANAP_ELEMENTARY_PROCEDURES_Outcome value;

    Outcome();
    Outcome(const Outcome &);
    Outcome(procedureCode, criticality, const value &);

    Outcome & operator = (const Outcome &);
    int operator == (const Outcome &) const;
    int operator != (const Outcome &) const;

    procedureCode & get_procedureCode();
    procedureCode get_procedureCode() const;
    void set_procedureCode(procedureCode);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    procedureCode procedureCode_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RANAP_PDU  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	initiatingMessage_chosen = 1,
	successfulOutcome_chosen = 2,
	unsuccessfulOutcome_chosen = 3,
	outcome_chosen = 4
    };
    typedef InitiatingMessage initiatingMessage;
    typedef SuccessfulOutcome successfulOutcome;
    typedef UnsuccessfulOutcome unsuccessfulOutcome;
    typedef Outcome outcome;

    RANAP_PDU();
    RANAP_PDU(const RANAP_PDU &);
    ~RANAP_PDU();

    RANAP_PDU & operator = (const RANAP_PDU &);
    int operator == (const RANAP_PDU &) const;
    int operator != (const RANAP_PDU &) const;

    initiatingMessage *get_initiatingMessage();
    const initiatingMessage *get_initiatingMessage() const;
    void set_initiatingMessage(const initiatingMessage &);

    successfulOutcome *get_successfulOutcome();
    const successfulOutcome *get_successfulOutcome() const;
    void set_successfulOutcome(const successfulOutcome &);

    unsuccessfulOutcome *get_unsuccessfulOutcome();
    const unsuccessfulOutcome *get_unsuccessfulOutcome() const;
    void set_unsuccessfulOutcome(const unsuccessfulOutcome &);

    outcome *get_outcome();
    const outcome *get_outcome() const;
    void set_outcome(const outcome &);
private:
    union {
	initiatingMessage *initiatingMessage_field;
	successfulOutcome *successfulOutcome_field;
	unsuccessfulOutcome *unsuccessfulOutcome_field;
	outcome *outcome_field;
    };
    void cleanup();
};

typedef OSS_UINT32 EncryptionAlgorithm;

typedef OSS_UINT32 ChosenEncryptionAlgorithm;

typedef OSS_UINT32 IntegrityProtectionAlgorithm;

typedef OSS_UINT32 ChosenIntegrityProtectionAlgorithm;

typedef OSS_UINT32 DRX_CycleLengthCoefficient;

typedef OSS_UINT32 HS_DSCH_MAC_d_Flow_ID;

typedef OSS_UINT32 InformationTransferID;

typedef OSS_UINT32 NumberOfSteps;

typedef OSS_UINT32 VerticalAccuracyCode;

typedef OssString ClassmarkInformation2;

typedef OssString ClassmarkInformation3;

typedef OssString GERAN_BSC_Container;

typedef OssString GERAN_Classmark;

typedef OssBitString IuSignallingConnectionIdentifier;

typedef OssString L3_Information;

typedef OssString NAS_PDU;

typedef OssString NewBSS_To_OldBSS_Information;

typedef OssString OldBSS_ToNewBSS_Information;

typedef OssString OMC_ID;

typedef OssString PositionDataSpecificToGERANIuMode;

typedef OssString RAC;

typedef OssString RRC_Container;

typedef OssString TraceReference;

typedef OssString TraceType;

typedef OssBitString TransportLayerAddress;

typedef OssString TriggerID;

class OSS_PUBLIC PrivateIE_ID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	local_chosen = 1,
	global_chosen = 2
    };
    typedef OSS_UINT32 local;
    typedef OssEncOID global;

    PrivateIE_ID();
    PrivateIE_ID(const PrivateIE_ID &);
    ~PrivateIE_ID();

    PrivateIE_ID & operator = (const PrivateIE_ID &);
    int operator == (const PrivateIE_ID &) const;
    int operator != (const PrivateIE_ID &) const;

    local *get_local();
    const local *get_local() const;
    void set_local(local);

    global *get_global();
    const global *get_global() const;
    void set_global(const global &);
private:
    union {
	local local_field;
	OSSC::COssEncOID global_field;
    };
    void cleanup();
};

typedef OSS_UINT32 ProtocolExtensionID;

typedef OSS_UINT32 ProtocolIE_ID;

class OSS_PUBLIC __shared9 : public OssList  /* SEQUENCE OF */
{
public:
    typedef OSS_UINT32 component;

    __shared9();
    __shared9(const __shared9 &);
    ~__shared9();

    __shared9 & operator = (const __shared9 &);
    int operator == (const __shared9 &) const;
    int operator != (const __shared9 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(component );
    OssIndex prepend(__shared9 *);
    OssIndex insert_after(OssIndex, component );
    OssIndex insert_after(OssIndex, __shared9 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared9 *extract_after(OssIndex, OssIndex);
};

typedef __shared9 RAB_Parameter_MaxBitrateList;

typedef __shared9 RAB_Parameter_GuaranteedBitrateList;

class OSS_PUBLIC __seq50;

class OSS_PUBLIC __shared11 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq50 component;

    __shared11();
    __shared11(const __shared11 &);
    ~__shared11();

    __shared11 & operator = (const __shared11 &);
    int operator == (const __shared11 &) const;
    int operator != (const __shared11 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared11 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared11 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared11 *extract_after(OssIndex, OssIndex);
};

typedef __shared11 SDU_Parameters;

class OSS_PUBLIC AllocationOrRetentionPriority   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 priorityLevel;
    typedef enum Pre_emptionCapability pre_emptionCapability;
    typedef enum Pre_emptionVulnerability pre_emptionVulnerability;
    typedef enum QueuingAllowed queuingAllowed;
    typedef __shared4 iE_Extensions;

    AllocationOrRetentionPriority();
    AllocationOrRetentionPriority(const AllocationOrRetentionPriority &);
    AllocationOrRetentionPriority(priorityLevel, pre_emptionCapability, pre_emptionVulnerability, 
	queuingAllowed, const iE_Extensions &);
    AllocationOrRetentionPriority(priorityLevel, pre_emptionCapability, pre_emptionVulnerability, 
	queuingAllowed);

    AllocationOrRetentionPriority & operator = (const AllocationOrRetentionPriority &);
    int operator == (const AllocationOrRetentionPriority &) const;
    int operator != (const AllocationOrRetentionPriority &) const;

    priorityLevel & get_priorityLevel();
    priorityLevel get_priorityLevel() const;
    void set_priorityLevel(priorityLevel);

    pre_emptionCapability & get_pre_emptionCapability();
    pre_emptionCapability get_pre_emptionCapability() const;
    void set_pre_emptionCapability(pre_emptionCapability);

    pre_emptionVulnerability & get_pre_emptionVulnerability();
    pre_emptionVulnerability get_pre_emptionVulnerability() const;
    void set_pre_emptionVulnerability(pre_emptionVulnerability);

    queuingAllowed & get_queuingAllowed();
    queuingAllowed get_queuingAllowed() const;
    void set_queuingAllowed(queuingAllowed);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    priorityLevel priorityLevel_field;
    pre_emptionCapability pre_emptionCapability_field;
    pre_emptionVulnerability pre_emptionVulnerability_field;
    queuingAllowed queuingAllowed_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq38;

class OSS_PUBLIC __seqof32 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq38 component;

    __seqof32();
    __seqof32(const __seqof32 &);
    ~__seqof32();

    __seqof32 & operator = (const __seqof32 &);
    int operator == (const __seqof32 &) const;
    int operator != (const __seqof32 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof32 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof32 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof32 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_Parameters   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum TrafficClass trafficClass;
    typedef enum RAB_AsymmetryIndicator rAB_AsymmetryIndicator;
    typedef __shared9 maxBitrate;
    typedef __shared9 guaranteedBitRate;
    typedef enum DeliveryOrder deliveryOrder;
    typedef OSS_UINT32 maxSDU_Size;
    typedef __shared11 sDU_Parameters;
    typedef OSS_UINT32 transferDelay;
    typedef OSS_UINT32 trafficHandlingPriority;
    typedef AllocationOrRetentionPriority allocationOrRetentionPriority;
    typedef enum SourceStatisticsDescriptor sourceStatisticsDescriptor;
    typedef enum RelocationRequirement relocationRequirement;
    typedef __seqof32 iE_Extensions;

    RAB_Parameters();
    RAB_Parameters(const RAB_Parameters &);
    RAB_Parameters(trafficClass, rAB_AsymmetryIndicator, const maxBitrate &, const guaranteedBitRate &, 
	deliveryOrder, maxSDU_Size, const sDU_Parameters &, transferDelay, trafficHandlingPriority, 
	const allocationOrRetentionPriority &, sourceStatisticsDescriptor, relocationRequirement, 
	const iE_Extensions &);
    RAB_Parameters(trafficClass, rAB_AsymmetryIndicator, const maxBitrate &, deliveryOrder, 
	maxSDU_Size, const sDU_Parameters &);

    RAB_Parameters & operator = (const RAB_Parameters &);
    int operator == (const RAB_Parameters &) const;
    int operator != (const RAB_Parameters &) const;

    trafficClass & get_trafficClass();
    trafficClass get_trafficClass() const;
    void set_trafficClass(trafficClass);

    rAB_AsymmetryIndicator & get_rAB_AsymmetryIndicator();
    rAB_AsymmetryIndicator get_rAB_AsymmetryIndicator() const;
    void set_rAB_AsymmetryIndicator(rAB_AsymmetryIndicator);

    maxBitrate & get_maxBitrate();
    const maxBitrate & get_maxBitrate() const;
    void set_maxBitrate(const maxBitrate &);

    guaranteedBitRate *get_guaranteedBitRate();
    const guaranteedBitRate *get_guaranteedBitRate() const;
    void set_guaranteedBitRate(const guaranteedBitRate &);
    int guaranteedBitRate_is_present() const;
    void omit_guaranteedBitRate();

    deliveryOrder & get_deliveryOrder();
    deliveryOrder get_deliveryOrder() const;
    void set_deliveryOrder(deliveryOrder);

    maxSDU_Size & get_maxSDU_Size();
    maxSDU_Size get_maxSDU_Size() const;
    void set_maxSDU_Size(maxSDU_Size);

    sDU_Parameters & get_sDU_Parameters();
    const sDU_Parameters & get_sDU_Parameters() const;
    void set_sDU_Parameters(const sDU_Parameters &);

    transferDelay *get_transferDelay();
    const transferDelay *get_transferDelay() const;
    void set_transferDelay(transferDelay);
    int transferDelay_is_present() const;
    void omit_transferDelay();

    trafficHandlingPriority *get_trafficHandlingPriority();
    const trafficHandlingPriority *get_trafficHandlingPriority() const;
    void set_trafficHandlingPriority(trafficHandlingPriority);
    int trafficHandlingPriority_is_present() const;
    void omit_trafficHandlingPriority();

    allocationOrRetentionPriority *get_allocationOrRetentionPriority();
    const allocationOrRetentionPriority *get_allocationOrRetentionPriority() const;
    void set_allocationOrRetentionPriority(const allocationOrRetentionPriority &);
    int allocationOrRetentionPriority_is_present() const;
    void omit_allocationOrRetentionPriority();

    sourceStatisticsDescriptor *get_sourceStatisticsDescriptor();
    const sourceStatisticsDescriptor *get_sourceStatisticsDescriptor() const;
    void set_sourceStatisticsDescriptor(sourceStatisticsDescriptor);
    int sourceStatisticsDescriptor_is_present() const;
    void omit_sourceStatisticsDescriptor();

    relocationRequirement *get_relocationRequirement();
    const relocationRequirement *get_relocationRequirement() const;
    void set_relocationRequirement(relocationRequirement);
    int relocationRequirement_is_present() const;
    void omit_relocationRequirement();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    trafficClass trafficClass_field;
    rAB_AsymmetryIndicator rAB_AsymmetryIndicator_field;
    maxBitrate maxBitrate_field;
    guaranteedBitRate guaranteedBitRate_field;
    deliveryOrder deliveryOrder_field;
    maxSDU_Size maxSDU_Size_field;
    sDU_Parameters sDU_Parameters_field;
    transferDelay transferDelay_field;
    trafficHandlingPriority trafficHandlingPriority_field;
    allocationOrRetentionPriority allocationOrRetentionPriority_field;
    sourceStatisticsDescriptor sourceStatisticsDescriptor_field;
    relocationRequirement relocationRequirement_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC UserPlaneInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum UserPlaneMode userPlaneMode;
    typedef OssBitString uP_ModeVersions;
    typedef __shared4 iE_Extensions;

    UserPlaneInformation();
    UserPlaneInformation(const UserPlaneInformation &);
    UserPlaneInformation(userPlaneMode, const uP_ModeVersions &, const iE_Extensions &);
    UserPlaneInformation(userPlaneMode, const uP_ModeVersions &);

    UserPlaneInformation & operator = (const UserPlaneInformation &);
    int operator == (const UserPlaneInformation &) const;
    int operator != (const UserPlaneInformation &) const;

    userPlaneMode & get_userPlaneMode();
    userPlaneMode get_userPlaneMode() const;
    void set_userPlaneMode(userPlaneMode);

    uP_ModeVersions & get_uP_ModeVersions();
    const uP_ModeVersions & get_uP_ModeVersions() const;
    void set_uP_ModeVersions(const uP_ModeVersions &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    userPlaneMode userPlaneMode_field;
    uP_ModeVersions uP_ModeVersions_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC IuTransportAssociation  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	gTP_TEI_chosen = 1,
	bindingID_chosen = 2
    };
    typedef OssString gTP_TEI;
    typedef OssString bindingID;

    IuTransportAssociation();
    IuTransportAssociation(const IuTransportAssociation &);
    ~IuTransportAssociation();

    IuTransportAssociation & operator = (const IuTransportAssociation &);
    int operator == (const IuTransportAssociation &) const;
    int operator != (const IuTransportAssociation &) const;

    gTP_TEI *get_gTP_TEI();
    const gTP_TEI *get_gTP_TEI() const;
    void set_gTP_TEI(const gTP_TEI &);

    bindingID *get_bindingID();
    const bindingID *get_bindingID() const;
    void set_bindingID(const bindingID &);
private:
    union {
	OSSC::COssString gTP_TEI_field;
	OSSC::COssString bindingID_field;
    };
    void cleanup();
};

class OSS_PUBLIC TransportLayerInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString transportLayerAddress;
    typedef IuTransportAssociation iuTransportAssociation;
    typedef __shared4 iE_Extensions;

    TransportLayerInformation();
    TransportLayerInformation(const TransportLayerInformation &);
    TransportLayerInformation(const transportLayerAddress &, const iuTransportAssociation &, 
	const iE_Extensions &);
    TransportLayerInformation(const transportLayerAddress &, const iuTransportAssociation &);

    TransportLayerInformation & operator = (const TransportLayerInformation &);
    int operator == (const TransportLayerInformation &) const;
    int operator != (const TransportLayerInformation &) const;

    transportLayerAddress & get_transportLayerAddress();
    const transportLayerAddress & get_transportLayerAddress() const;
    void set_transportLayerAddress(const transportLayerAddress &);

    iuTransportAssociation & get_iuTransportAssociation();
    const iuTransportAssociation & get_iuTransportAssociation() const;
    void set_iuTransportAssociation(const iuTransportAssociation &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    transportLayerAddress transportLayerAddress_field;
    iuTransportAssociation iuTransportAssociation_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupOrModifyItemFirst   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OssBitString nAS_SynchronisationIndicator;
    typedef RAB_Parameters rAB_Parameters;
    typedef UserPlaneInformation userPlaneInformation;
    typedef TransportLayerInformation transportLayerInformation;
    typedef enum Service_Handover service_Handover;
    typedef __shared4 iE_Extensions;

    RAB_SetupOrModifyItemFirst();
    RAB_SetupOrModifyItemFirst(const RAB_SetupOrModifyItemFirst &);
    RAB_SetupOrModifyItemFirst(const rAB_ID &, const nAS_SynchronisationIndicator &, 
	const rAB_Parameters &, const userPlaneInformation &, const transportLayerInformation &, 
	service_Handover, const iE_Extensions &);
    RAB_SetupOrModifyItemFirst(const rAB_ID &);

    RAB_SetupOrModifyItemFirst & operator = (const RAB_SetupOrModifyItemFirst &);
    int operator == (const RAB_SetupOrModifyItemFirst &) const;
    int operator != (const RAB_SetupOrModifyItemFirst &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    nAS_SynchronisationIndicator *get_nAS_SynchronisationIndicator();
    const nAS_SynchronisationIndicator *get_nAS_SynchronisationIndicator() const;
    void set_nAS_SynchronisationIndicator(const nAS_SynchronisationIndicator &);
    int nAS_SynchronisationIndicator_is_present() const;
    void omit_nAS_SynchronisationIndicator();

    rAB_Parameters *get_rAB_Parameters();
    const rAB_Parameters *get_rAB_Parameters() const;
    void set_rAB_Parameters(const rAB_Parameters &);
    int rAB_Parameters_is_present() const;
    void omit_rAB_Parameters();

    userPlaneInformation *get_userPlaneInformation();
    const userPlaneInformation *get_userPlaneInformation() const;
    void set_userPlaneInformation(const userPlaneInformation &);
    int userPlaneInformation_is_present() const;
    void omit_userPlaneInformation();

    transportLayerInformation *get_transportLayerInformation();
    const transportLayerInformation *get_transportLayerInformation() const;
    void set_transportLayerInformation(const transportLayerInformation &);
    int transportLayerInformation_is_present() const;
    void omit_transportLayerInformation();

    service_Handover *get_service_Handover();
    const service_Handover *get_service_Handover() const;
    void set_service_Handover(service_Handover);
    int service_Handover_is_present() const;
    void omit_service_Handover();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    nAS_SynchronisationIndicator nAS_SynchronisationIndicator_field;
    rAB_Parameters rAB_Parameters_field;
    userPlaneInformation userPlaneInformation_field;
    transportLayerInformation transportLayerInformation_field;
    service_Handover service_Handover_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupOrModifyItem_IEs_FirstValue : public OssConstrainedOpenType
{
public:
    RAB_SetupOrModifyItem_IEs_FirstValue();
    RAB_SetupOrModifyItem_IEs_FirstValue(const RAB_SetupOrModifyItem_IEs_FirstValue &);
    ~RAB_SetupOrModifyItem_IEs_FirstValue();
    RAB_SetupOrModifyItem_IEs_FirstValue & operator = (const RAB_SetupOrModifyItem_IEs_FirstValue &);
    int operator == (const RAB_SetupOrModifyItem_IEs_FirstValue &) const;
    int operator != (const RAB_SetupOrModifyItem_IEs_FirstValue &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupOrModifyItemFirst *get_RAB_SetupOrModifyItemFirst();
    const RAB_SetupOrModifyItemFirst *get_RAB_SetupOrModifyItemFirst() const;
    void set_RAB_SetupOrModifyItemFirst(const RAB_SetupOrModifyItemFirst &);
    RAB_SetupOrModifyItemFirst *release_RAB_SetupOrModifyItemFirst();
    void set_RAB_SetupOrModifyItemFirst(RAB_SetupOrModifyItemFirst *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC PDP_TypeInformation : public OssList  /* SEQUENCE OF */
{
public:
    typedef enum PDP_Type component;

    PDP_TypeInformation();
    PDP_TypeInformation(const PDP_TypeInformation &);
    ~PDP_TypeInformation();

    PDP_TypeInformation & operator = (const PDP_TypeInformation &);
    int operator == (const PDP_TypeInformation &) const;
    int operator != (const PDP_TypeInformation &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(component );
    OssIndex prepend(PDP_TypeInformation *);
    OssIndex insert_after(OssIndex, component );
    OssIndex insert_after(OssIndex, PDP_TypeInformation *);

    int remove_front();
    int remove_after(OssIndex);

    PDP_TypeInformation *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared13;

class OSS_PUBLIC __shared14 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared13 component;

    __shared14();
    __shared14(const __shared14 &);
    ~__shared14();

    __shared14 & operator = (const __shared14 &);
    int operator == (const __shared14 &) const;
    int operator != (const __shared14 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared14 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared14 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared14 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_SetupOrModifyItemSecond   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef PDP_TypeInformation pDP_TypeInformation;
    typedef enum DataVolumeReportingIndication dataVolumeReportingIndication;
    typedef OSS_UINT32 dl_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 ul_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 dl_N_PDU_SequenceNumber;
    typedef OSS_UINT32 ul_N_PDU_SequenceNumber;
    typedef __shared14 iE_Extensions;

    RAB_SetupOrModifyItemSecond();
    RAB_SetupOrModifyItemSecond(const RAB_SetupOrModifyItemSecond &);
    RAB_SetupOrModifyItemSecond(const pDP_TypeInformation &, dataVolumeReportingIndication, 
	dl_GTP_PDU_SequenceNumber, ul_GTP_PDU_SequenceNumber, dl_N_PDU_SequenceNumber, ul_N_PDU_SequenceNumber, 
	const iE_Extensions &);

    RAB_SetupOrModifyItemSecond & operator = (const RAB_SetupOrModifyItemSecond &);
    int operator == (const RAB_SetupOrModifyItemSecond &) const;
    int operator != (const RAB_SetupOrModifyItemSecond &) const;

    pDP_TypeInformation *get_pDP_TypeInformation();
    const pDP_TypeInformation *get_pDP_TypeInformation() const;
    void set_pDP_TypeInformation(const pDP_TypeInformation &);
    int pDP_TypeInformation_is_present() const;
    void omit_pDP_TypeInformation();

    dataVolumeReportingIndication *get_dataVolumeReportingIndication();
    const dataVolumeReportingIndication *get_dataVolumeReportingIndication() const;
    void set_dataVolumeReportingIndication(dataVolumeReportingIndication);
    int dataVolumeReportingIndication_is_present() const;
    void omit_dataVolumeReportingIndication();

    dl_GTP_PDU_SequenceNumber *get_dl_GTP_PDU_SequenceNumber();
    const dl_GTP_PDU_SequenceNumber *get_dl_GTP_PDU_SequenceNumber() const;
    void set_dl_GTP_PDU_SequenceNumber(dl_GTP_PDU_SequenceNumber);
    int dl_GTP_PDU_SequenceNumber_is_present() const;
    void omit_dl_GTP_PDU_SequenceNumber();

    ul_GTP_PDU_SequenceNumber *get_ul_GTP_PDU_SequenceNumber();
    const ul_GTP_PDU_SequenceNumber *get_ul_GTP_PDU_SequenceNumber() const;
    void set_ul_GTP_PDU_SequenceNumber(ul_GTP_PDU_SequenceNumber);
    int ul_GTP_PDU_SequenceNumber_is_present() const;
    void omit_ul_GTP_PDU_SequenceNumber();

    dl_N_PDU_SequenceNumber *get_dl_N_PDU_SequenceNumber();
    const dl_N_PDU_SequenceNumber *get_dl_N_PDU_SequenceNumber() const;
    void set_dl_N_PDU_SequenceNumber(dl_N_PDU_SequenceNumber);
    int dl_N_PDU_SequenceNumber_is_present() const;
    void omit_dl_N_PDU_SequenceNumber();

    ul_N_PDU_SequenceNumber *get_ul_N_PDU_SequenceNumber();
    const ul_N_PDU_SequenceNumber *get_ul_N_PDU_SequenceNumber() const;
    void set_ul_N_PDU_SequenceNumber(ul_N_PDU_SequenceNumber);
    int ul_N_PDU_SequenceNumber_is_present() const;
    void omit_ul_N_PDU_SequenceNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pDP_TypeInformation pDP_TypeInformation_field;
    dataVolumeReportingIndication dataVolumeReportingIndication_field;
    dl_GTP_PDU_SequenceNumber dl_GTP_PDU_SequenceNumber_field;
    ul_GTP_PDU_SequenceNumber ul_GTP_PDU_SequenceNumber_field;
    dl_N_PDU_SequenceNumber dl_N_PDU_SequenceNumber_field;
    ul_N_PDU_SequenceNumber ul_N_PDU_SequenceNumber_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupOrModifyItem_IEs_SecondValue : public OssConstrainedOpenType
{
public:
    RAB_SetupOrModifyItem_IEs_SecondValue();
    RAB_SetupOrModifyItem_IEs_SecondValue(const RAB_SetupOrModifyItem_IEs_SecondValue &);
    ~RAB_SetupOrModifyItem_IEs_SecondValue();
    RAB_SetupOrModifyItem_IEs_SecondValue & operator = (const RAB_SetupOrModifyItem_IEs_SecondValue &);
    int operator == (const RAB_SetupOrModifyItem_IEs_SecondValue &) const;
    int operator != (const RAB_SetupOrModifyItem_IEs_SecondValue &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupOrModifyItemSecond *get_RAB_SetupOrModifyItemSecond();
    const RAB_SetupOrModifyItemSecond *get_RAB_SetupOrModifyItemSecond() const;
    void set_RAB_SetupOrModifyItemSecond(const RAB_SetupOrModifyItemSecond &);
    RAB_SetupOrModifyItemSecond *release_RAB_SetupOrModifyItemSecond();
    void set_RAB_SetupOrModifyItemSecond(RAB_SetupOrModifyItemSecond *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC ProtocolIE_FieldPair   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality firstCriticality;
    typedef RAB_SetupOrModifyItem_IEs_FirstValue firstValue;
    typedef enum Criticality secondCriticality;
    typedef RAB_SetupOrModifyItem_IEs_SecondValue secondValue;

    ProtocolIE_FieldPair();
    ProtocolIE_FieldPair(const ProtocolIE_FieldPair &);
    ProtocolIE_FieldPair(id, firstCriticality, const firstValue &, secondCriticality, 
	const secondValue &);

    ProtocolIE_FieldPair & operator = (const ProtocolIE_FieldPair &);
    int operator == (const ProtocolIE_FieldPair &) const;
    int operator != (const ProtocolIE_FieldPair &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    firstCriticality & get_firstCriticality();
    firstCriticality get_firstCriticality() const;
    void set_firstCriticality(firstCriticality);

    firstValue & get_firstValue();
    const firstValue & get_firstValue() const;
    void set_firstValue(const firstValue &);

    secondCriticality & get_secondCriticality();
    secondCriticality get_secondCriticality() const;
    void set_secondCriticality(secondCriticality);

    secondValue & get_secondValue();
    const secondValue & get_secondValue() const;
    void set_secondValue(const secondValue &);
private:
    id id_field;
    firstCriticality firstCriticality_field;
    firstValue firstValue_field;
    secondCriticality secondCriticality_field;
    secondValue secondValue_field;
};

class OSS_PUBLIC PrivateMessage_IEs_Value : public OssConstrainedOpenType
{
public:
    PrivateMessage_IEs_Value();
    PrivateMessage_IEs_Value(const PrivateMessage_IEs_Value &);
    ~PrivateMessage_IEs_Value();
    PrivateMessage_IEs_Value & operator = (const PrivateMessage_IEs_Value &);
    int operator == (const PrivateMessage_IEs_Value &) const;
    int operator != (const PrivateMessage_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC PrivateIE_Field   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef PrivateIE_ID id;
    typedef enum Criticality criticality;
    typedef PrivateMessage_IEs_Value value;

    PrivateIE_Field();
    PrivateIE_Field(const PrivateIE_Field &);
    PrivateIE_Field(const id &, criticality, const value &);

    PrivateIE_Field & operator = (const PrivateIE_Field &);
    int operator == (const PrivateIE_Field &) const;
    int operator != (const PrivateIE_Field &) const;

    id & get_id();
    const id & get_id() const;
    void set_id(const id &);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef OSS_UINT32 PriorityLevel;

class OSS_PUBLIC __shared3   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef PrivateMessage_IEs_Value extensionValue;

    __shared3();
    __shared3(const __shared3 &);
    __shared3(id, criticality, const extensionValue &);

    __shared3 & operator = (const __shared3 &);
    int operator == (const __shared3 &) const;
    int operator != (const __shared3 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __shared12 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared9 component;

    __shared12();
    __shared12(const __shared12 &);
    ~__shared12();

    __shared12 & operator = (const __shared12 &);
    int operator == (const __shared12 &) const;
    int operator != (const __shared12 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared12 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared12 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared12 *extract_after(OssIndex, OssIndex);
};

typedef __shared12 Alt_RAB_Parameter_MaxBitrates;

class OSS_PUBLIC Alt_RAB_Parameter_MaxBitrateInf   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum Alt_RAB_Parameter_MaxBitrateType altMaxBitrateType;
    typedef __shared12 altMaxBitrates;

    Alt_RAB_Parameter_MaxBitrateInf();
    Alt_RAB_Parameter_MaxBitrateInf(const Alt_RAB_Parameter_MaxBitrateInf &);
    Alt_RAB_Parameter_MaxBitrateInf(altMaxBitrateType, const altMaxBitrates &);
    Alt_RAB_Parameter_MaxBitrateInf(altMaxBitrateType);

    Alt_RAB_Parameter_MaxBitrateInf & operator = (const Alt_RAB_Parameter_MaxBitrateInf &);
    int operator == (const Alt_RAB_Parameter_MaxBitrateInf &) const;
    int operator != (const Alt_RAB_Parameter_MaxBitrateInf &) const;

    altMaxBitrateType & get_altMaxBitrateType();
    altMaxBitrateType get_altMaxBitrateType() const;
    void set_altMaxBitrateType(altMaxBitrateType);

    altMaxBitrates *get_altMaxBitrates();
    const altMaxBitrates *get_altMaxBitrates() const;
    void set_altMaxBitrates(const altMaxBitrates &);
    int altMaxBitrates_is_present() const;
    void omit_altMaxBitrates();
private:
    OSS_UINT32 bit_mask;
    altMaxBitrateType altMaxBitrateType_field;
    altMaxBitrates altMaxBitrates_field;
};

typedef __shared12 Alt_RAB_Parameter_GuaranteedBitrates;

class OSS_PUBLIC Alt_RAB_Parameter_GuaranteedBitrateInf   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum Alt_RAB_Parameter_GuaranteedBitrateType altGuaranteedBitrateType;
    typedef __shared12 altGuaranteedBitrates;

    Alt_RAB_Parameter_GuaranteedBitrateInf();
    Alt_RAB_Parameter_GuaranteedBitrateInf(const Alt_RAB_Parameter_GuaranteedBitrateInf &);
    Alt_RAB_Parameter_GuaranteedBitrateInf(altGuaranteedBitrateType, const altGuaranteedBitrates &);
    Alt_RAB_Parameter_GuaranteedBitrateInf(altGuaranteedBitrateType);

    Alt_RAB_Parameter_GuaranteedBitrateInf & operator = (const Alt_RAB_Parameter_GuaranteedBitrateInf &);
    int operator == (const Alt_RAB_Parameter_GuaranteedBitrateInf &) const;
    int operator != (const Alt_RAB_Parameter_GuaranteedBitrateInf &) const;

    altGuaranteedBitrateType & get_altGuaranteedBitrateType();
    altGuaranteedBitrateType get_altGuaranteedBitrateType() const;
    void set_altGuaranteedBitrateType(altGuaranteedBitrateType);

    altGuaranteedBitrates *get_altGuaranteedBitrates();
    const altGuaranteedBitrates *get_altGuaranteedBitrates() const;
    void set_altGuaranteedBitrates(const altGuaranteedBitrates &);
    int altGuaranteedBitrates_is_present() const;
    void omit_altGuaranteedBitrates();
private:
    OSS_UINT32 bit_mask;
    altGuaranteedBitrateType altGuaranteedBitrateType_field;
    altGuaranteedBitrates altGuaranteedBitrates_field;
};

class OSS_PUBLIC Alt_RAB_Parameters   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef Alt_RAB_Parameter_MaxBitrateInf altMaxBitrateInf;
    typedef Alt_RAB_Parameter_GuaranteedBitrateInf altGuaranteedBitRateInf;
    typedef __shared4 iE_Extensions;

    Alt_RAB_Parameters();
    Alt_RAB_Parameters(const Alt_RAB_Parameters &);
    Alt_RAB_Parameters(const altMaxBitrateInf &, const altGuaranteedBitRateInf &, 
	const iE_Extensions &);

    Alt_RAB_Parameters & operator = (const Alt_RAB_Parameters &);
    int operator == (const Alt_RAB_Parameters &) const;
    int operator != (const Alt_RAB_Parameters &) const;

    altMaxBitrateInf *get_altMaxBitrateInf();
    const altMaxBitrateInf *get_altMaxBitrateInf() const;
    void set_altMaxBitrateInf(const altMaxBitrateInf &);
    int altMaxBitrateInf_is_present() const;
    void omit_altMaxBitrateInf();

    altGuaranteedBitRateInf *get_altGuaranteedBitRateInf();
    const altGuaranteedBitRateInf *get_altGuaranteedBitRateInf() const;
    void set_altGuaranteedBitRateInf(const altGuaranteedBitRateInf &);
    int altGuaranteedBitRateInf_is_present() const;
    void omit_altGuaranteedBitRateInf();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    altMaxBitrateInf altMaxBitrateInf_field;
    altGuaranteedBitRateInf altGuaranteedBitRateInf_field;
    iE_Extensions iE_Extensions_field;
};

typedef OSS_UINT32 GuaranteedBitrate;

typedef __shared9 Alt_RAB_Parameter_GuaranteedBitrateList;

typedef OSS_UINT32 MaxBitrate;

typedef __shared9 Alt_RAB_Parameter_MaxBitrateList;

class OSS_PUBLIC SAI   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OssString lAC;
    typedef OssString sAC;
    typedef __shared4 iE_Extensions;

    SAI();
    SAI(const SAI &);
    SAI(const pLMNidentity &, const lAC &, const sAC &, const iE_Extensions &);
    SAI(const pLMNidentity &, const lAC &, const sAC &);

    SAI & operator = (const SAI &);
    int operator == (const SAI &) const;
    int operator != (const SAI &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    lAC & get_lAC();
    const lAC & get_lAC() const;
    void set_lAC(const lAC &);

    sAC & get_sAC();
    const sAC & get_sAC() const;
    void set_sAC(const sAC &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    lAC lAC_field;
    sAC sAC_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GeographicalCoordinates   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum _enum1 latitudeSign;
    typedef OSS_UINT32 latitude;
    typedef OSS_INT32 longitude;
    typedef __shared4 iE_Extensions;

    GeographicalCoordinates();
    GeographicalCoordinates(const GeographicalCoordinates &);
    GeographicalCoordinates(latitudeSign, latitude, longitude, const iE_Extensions &);
    GeographicalCoordinates(latitudeSign, latitude, longitude);

    GeographicalCoordinates & operator = (const GeographicalCoordinates &);
    int operator == (const GeographicalCoordinates &) const;
    int operator != (const GeographicalCoordinates &) const;

    latitudeSign & get_latitudeSign();
    latitudeSign get_latitudeSign() const;
    void set_latitudeSign(latitudeSign);

    latitude & get_latitude();
    latitude get_latitude() const;
    void set_latitude(latitude);

    longitude & get_longitude();
    longitude get_longitude() const;
    void set_longitude(longitude);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    latitudeSign latitudeSign_field;
    latitude latitude_field;
    longitude longitude_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __shared24   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef __shared4 iE_Extensions;

    __shared24();
    __shared24(const __shared24 &);
    __shared24(const geographicalCoordinates &, const iE_Extensions &);
    __shared24(const geographicalCoordinates &);

    __shared24 & operator = (const __shared24 &);
    int operator == (const __shared24 &) const;
    int operator != (const __shared24 &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared24 GA_Point;

class OSS_PUBLIC GA_PointWithUnCertainty   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef __shared4 iE_Extensions;
    typedef OSS_UINT32 uncertaintyCode;

    GA_PointWithUnCertainty();
    GA_PointWithUnCertainty(const GA_PointWithUnCertainty &);
    GA_PointWithUnCertainty(const geographicalCoordinates &, const iE_Extensions &, 
	uncertaintyCode);
    GA_PointWithUnCertainty(const geographicalCoordinates &, uncertaintyCode);

    GA_PointWithUnCertainty & operator = (const GA_PointWithUnCertainty &);
    int operator == (const GA_PointWithUnCertainty &) const;
    int operator != (const GA_PointWithUnCertainty &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();

    uncertaintyCode & get_uncertaintyCode();
    uncertaintyCode get_uncertaintyCode() const;
    void set_uncertaintyCode(uncertaintyCode);
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    iE_Extensions iE_Extensions_field;
    uncertaintyCode uncertaintyCode_field;
};

class OSS_PUBLIC __shared25 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared24 component;

    __shared25();
    __shared25(const __shared25 &);
    ~__shared25();

    __shared25 & operator = (const __shared25 &);
    int operator == (const __shared25 &) const;
    int operator != (const __shared25 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared25 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared25 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared25 *extract_after(OssIndex, OssIndex);
};

typedef __shared25 GA_Polygon;

class OSS_PUBLIC GA_UncertaintyEllipse   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 uncertaintySemi_major;
    typedef OSS_UINT32 uncertaintySemi_minor;
    typedef OSS_UINT32 orientationOfMajorAxis;

    GA_UncertaintyEllipse();
    GA_UncertaintyEllipse(const GA_UncertaintyEllipse &);
    GA_UncertaintyEllipse(uncertaintySemi_major, uncertaintySemi_minor, orientationOfMajorAxis);

    GA_UncertaintyEllipse & operator = (const GA_UncertaintyEllipse &);
    int operator == (const GA_UncertaintyEllipse &) const;
    int operator != (const GA_UncertaintyEllipse &) const;

    uncertaintySemi_major & get_uncertaintySemi_major();
    uncertaintySemi_major get_uncertaintySemi_major() const;
    void set_uncertaintySemi_major(uncertaintySemi_major);

    uncertaintySemi_minor & get_uncertaintySemi_minor();
    uncertaintySemi_minor get_uncertaintySemi_minor() const;
    void set_uncertaintySemi_minor(uncertaintySemi_minor);

    orientationOfMajorAxis & get_orientationOfMajorAxis();
    orientationOfMajorAxis get_orientationOfMajorAxis() const;
    void set_orientationOfMajorAxis(orientationOfMajorAxis);
private:
    uncertaintySemi_major uncertaintySemi_major_field;
    uncertaintySemi_minor uncertaintySemi_minor_field;
    orientationOfMajorAxis orientationOfMajorAxis_field;
};

class OSS_PUBLIC GA_PointWithUnCertaintyEllipse   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef GA_UncertaintyEllipse uncertaintyEllipse;
    typedef OSS_UINT32 confidence;
    typedef __shared4 iE_Extensions;

    GA_PointWithUnCertaintyEllipse();
    GA_PointWithUnCertaintyEllipse(const GA_PointWithUnCertaintyEllipse &);
    GA_PointWithUnCertaintyEllipse(const geographicalCoordinates &, const uncertaintyEllipse &, 
	confidence, const iE_Extensions &);
    GA_PointWithUnCertaintyEllipse(const geographicalCoordinates &, const uncertaintyEllipse &, 
	confidence);

    GA_PointWithUnCertaintyEllipse & operator = (const GA_PointWithUnCertaintyEllipse &);
    int operator == (const GA_PointWithUnCertaintyEllipse &) const;
    int operator != (const GA_PointWithUnCertaintyEllipse &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    uncertaintyEllipse & get_uncertaintyEllipse();
    const uncertaintyEllipse & get_uncertaintyEllipse() const;
    void set_uncertaintyEllipse(const uncertaintyEllipse &);

    confidence & get_confidence();
    confidence get_confidence() const;
    void set_confidence(confidence);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    uncertaintyEllipse uncertaintyEllipse_field;
    confidence confidence_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GA_AltitudeAndDirection   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum _enum2 directionOfAltitude;
    typedef OSS_UINT32 altitude;

    GA_AltitudeAndDirection();
    GA_AltitudeAndDirection(const GA_AltitudeAndDirection &);
    GA_AltitudeAndDirection(directionOfAltitude, altitude);

    GA_AltitudeAndDirection & operator = (const GA_AltitudeAndDirection &);
    int operator == (const GA_AltitudeAndDirection &) const;
    int operator != (const GA_AltitudeAndDirection &) const;

    directionOfAltitude & get_directionOfAltitude();
    directionOfAltitude get_directionOfAltitude() const;
    void set_directionOfAltitude(directionOfAltitude);

    altitude & get_altitude();
    altitude get_altitude() const;
    void set_altitude(altitude);
private:
    directionOfAltitude directionOfAltitude_field;
    altitude altitude_field;
};

class OSS_PUBLIC GA_PointWithAltitude   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef GA_AltitudeAndDirection altitudeAndDirection;
    typedef __shared4 iE_Extensions;

    GA_PointWithAltitude();
    GA_PointWithAltitude(const GA_PointWithAltitude &);
    GA_PointWithAltitude(const geographicalCoordinates &, const altitudeAndDirection &, 
	const iE_Extensions &);
    GA_PointWithAltitude(const geographicalCoordinates &, const altitudeAndDirection &);

    GA_PointWithAltitude & operator = (const GA_PointWithAltitude &);
    int operator == (const GA_PointWithAltitude &) const;
    int operator != (const GA_PointWithAltitude &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    altitudeAndDirection & get_altitudeAndDirection();
    const altitudeAndDirection & get_altitudeAndDirection() const;
    void set_altitudeAndDirection(const altitudeAndDirection &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    altitudeAndDirection altitudeAndDirection_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GA_PointWithAltitudeAndUncertaintyEllipsoid   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef GA_AltitudeAndDirection altitudeAndDirection;
    typedef GA_UncertaintyEllipse uncertaintyEllipse;
    typedef OSS_UINT32 uncertaintyAltitude;
    typedef OSS_UINT32 confidence;
    typedef __shared4 iE_Extensions;

    GA_PointWithAltitudeAndUncertaintyEllipsoid();
    GA_PointWithAltitudeAndUncertaintyEllipsoid(const GA_PointWithAltitudeAndUncertaintyEllipsoid &);
    GA_PointWithAltitudeAndUncertaintyEllipsoid(const geographicalCoordinates &, 
	const altitudeAndDirection &, const uncertaintyEllipse &, uncertaintyAltitude, confidence, 
	const iE_Extensions &);
    GA_PointWithAltitudeAndUncertaintyEllipsoid(const geographicalCoordinates &, 
	const altitudeAndDirection &, const uncertaintyEllipse &, uncertaintyAltitude, confidence);

    GA_PointWithAltitudeAndUncertaintyEllipsoid & operator = (const GA_PointWithAltitudeAndUncertaintyEllipsoid &);
    int operator == (const GA_PointWithAltitudeAndUncertaintyEllipsoid &) const;
    int operator != (const GA_PointWithAltitudeAndUncertaintyEllipsoid &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    altitudeAndDirection & get_altitudeAndDirection();
    const altitudeAndDirection & get_altitudeAndDirection() const;
    void set_altitudeAndDirection(const altitudeAndDirection &);

    uncertaintyEllipse & get_uncertaintyEllipse();
    const uncertaintyEllipse & get_uncertaintyEllipse() const;
    void set_uncertaintyEllipse(const uncertaintyEllipse &);

    uncertaintyAltitude & get_uncertaintyAltitude();
    uncertaintyAltitude get_uncertaintyAltitude() const;
    void set_uncertaintyAltitude(uncertaintyAltitude);

    confidence & get_confidence();
    confidence get_confidence() const;
    void set_confidence(confidence);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    altitudeAndDirection altitudeAndDirection_field;
    uncertaintyEllipse uncertaintyEllipse_field;
    uncertaintyAltitude uncertaintyAltitude_field;
    confidence confidence_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GA_EllipsoidArc   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef GeographicalCoordinates geographicalCoordinates;
    typedef OSS_UINT32 innerRadius;
    typedef OSS_UINT32 uncertaintyRadius;
    typedef OSS_UINT32 offsetAngle;
    typedef OSS_UINT32 includedAngle;
    typedef OSS_UINT32 confidence;
    typedef __shared4 iE_Extensions;

    GA_EllipsoidArc();
    GA_EllipsoidArc(const GA_EllipsoidArc &);
    GA_EllipsoidArc(const geographicalCoordinates &, innerRadius, uncertaintyRadius, 
	offsetAngle, includedAngle, confidence, const iE_Extensions &);
    GA_EllipsoidArc(const geographicalCoordinates &, innerRadius, uncertaintyRadius, 
	offsetAngle, includedAngle, confidence);

    GA_EllipsoidArc & operator = (const GA_EllipsoidArc &);
    int operator == (const GA_EllipsoidArc &) const;
    int operator != (const GA_EllipsoidArc &) const;

    geographicalCoordinates & get_geographicalCoordinates();
    const geographicalCoordinates & get_geographicalCoordinates() const;
    void set_geographicalCoordinates(const geographicalCoordinates &);

    innerRadius & get_innerRadius();
    innerRadius get_innerRadius() const;
    void set_innerRadius(innerRadius);

    uncertaintyRadius & get_uncertaintyRadius();
    uncertaintyRadius get_uncertaintyRadius() const;
    void set_uncertaintyRadius(uncertaintyRadius);

    offsetAngle & get_offsetAngle();
    offsetAngle get_offsetAngle() const;
    void set_offsetAngle(offsetAngle);

    includedAngle & get_includedAngle();
    includedAngle get_includedAngle() const;
    void set_includedAngle(includedAngle);

    confidence & get_confidence();
    confidence get_confidence() const;
    void set_confidence(confidence);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    geographicalCoordinates geographicalCoordinates_field;
    innerRadius innerRadius_field;
    uncertaintyRadius uncertaintyRadius_field;
    offsetAngle offsetAngle_field;
    includedAngle includedAngle_field;
    confidence confidence_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GeographicalArea  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	point_chosen = 1,
	pointWithUnCertainty_chosen = 2,
	polygon_chosen = 3,
	pointWithUncertaintyEllipse_chosen = 4,
	pointWithAltitude_chosen = 5,
	pointWithAltitudeAndUncertaintyEllipsoid_chosen = 6,
	ellipsoidArc_chosen = 7
    };
    typedef __shared24 point;
    typedef GA_PointWithUnCertainty pointWithUnCertainty;
    typedef __shared25 polygon;
    typedef GA_PointWithUnCertaintyEllipse pointWithUncertaintyEllipse;
    typedef GA_PointWithAltitude pointWithAltitude;
    typedef GA_PointWithAltitudeAndUncertaintyEllipsoid pointWithAltitudeAndUncertaintyEllipsoid;
    typedef GA_EllipsoidArc ellipsoidArc;

    GeographicalArea();
    GeographicalArea(const GeographicalArea &);
    ~GeographicalArea();

    GeographicalArea & operator = (const GeographicalArea &);
    int operator == (const GeographicalArea &) const;
    int operator != (const GeographicalArea &) const;

    point *get_point();
    const point *get_point() const;
    void set_point(const point &);

    pointWithUnCertainty *get_pointWithUnCertainty();
    const pointWithUnCertainty *get_pointWithUnCertainty() const;
    void set_pointWithUnCertainty(const pointWithUnCertainty &);

    polygon *get_polygon();
    const polygon *get_polygon() const;
    void set_polygon(const polygon &);

    pointWithUncertaintyEllipse *get_pointWithUncertaintyEllipse();
    const pointWithUncertaintyEllipse *get_pointWithUncertaintyEllipse() const;
    void set_pointWithUncertaintyEllipse(const pointWithUncertaintyEllipse &);

    pointWithAltitude *get_pointWithAltitude();
    const pointWithAltitude *get_pointWithAltitude() const;
    void set_pointWithAltitude(const pointWithAltitude &);

    pointWithAltitudeAndUncertaintyEllipsoid *get_pointWithAltitudeAndUncertaintyEllipsoid();
    const pointWithAltitudeAndUncertaintyEllipsoid *get_pointWithAltitudeAndUncertaintyEllipsoid() const;
    void set_pointWithAltitudeAndUncertaintyEllipsoid(const pointWithAltitudeAndUncertaintyEllipsoid &);

    ellipsoidArc *get_ellipsoidArc();
    const ellipsoidArc *get_ellipsoidArc() const;
    void set_ellipsoidArc(const ellipsoidArc &);
private:
    union {
	point *point_field;
	pointWithUnCertainty *pointWithUnCertainty_field;
	void *polygon_field;
	pointWithUncertaintyEllipse *pointWithUncertaintyEllipse_field;
	pointWithAltitude *pointWithAltitude_field;
	pointWithAltitudeAndUncertaintyEllipsoid *pointWithAltitudeAndUncertaintyEllipsoid_field;
	ellipsoidArc *ellipsoidArc_field;
    };
    void cleanup();
};

class OSS_PUBLIC AreaIdentity  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	sAI_chosen = 1,
	geographicalArea_chosen = 2
    };
    typedef SAI sAI;
    typedef GeographicalArea geographicalArea;

    AreaIdentity();
    AreaIdentity(const AreaIdentity &);
    ~AreaIdentity();

    AreaIdentity & operator = (const AreaIdentity &);
    int operator == (const AreaIdentity &) const;
    int operator != (const AreaIdentity &) const;

    sAI *get_sAI();
    const sAI *get_sAI() const;
    void set_sAI(const sAI &);

    geographicalArea *get_geographicalArea();
    const geographicalArea *get_geographicalArea() const;
    void set_geographicalArea(const geographicalArea &);
private:
    union {
	sAI *sAI_field;
	geographicalArea *geographicalArea_field;
    };
    void cleanup();
};

typedef __shared9 Ass_RAB_Parameter_MaxBitrateList;

typedef __shared9 Ass_RAB_Parameter_GuaranteedBitrateList;

class OSS_PUBLIC Ass_RAB_Parameters   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared9 assMaxBitrateInf;
    typedef __shared9 assGuaranteedBitRateInf;
    typedef __shared4 iE_Extensions;

    Ass_RAB_Parameters();
    Ass_RAB_Parameters(const Ass_RAB_Parameters &);
    Ass_RAB_Parameters(const assMaxBitrateInf &, const assGuaranteedBitRateInf &, 
	const iE_Extensions &);

    Ass_RAB_Parameters & operator = (const Ass_RAB_Parameters &);
    int operator == (const Ass_RAB_Parameters &) const;
    int operator != (const Ass_RAB_Parameters &) const;

    assMaxBitrateInf *get_assMaxBitrateInf();
    const assMaxBitrateInf *get_assMaxBitrateInf() const;
    void set_assMaxBitrateInf(const assMaxBitrateInf &);
    int assMaxBitrateInf_is_present() const;
    void omit_assMaxBitrateInf();

    assGuaranteedBitRateInf *get_assGuaranteedBitRateInf();
    const assGuaranteedBitRateInf *get_assGuaranteedBitRateInf() const;
    void set_assGuaranteedBitRateInf(const assGuaranteedBitRateInf &);
    int assGuaranteedBitRateInf_is_present() const;
    void omit_assGuaranteedBitRateInf();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    assMaxBitrateInf assMaxBitrateInf_field;
    assGuaranteedBitRateInf assGuaranteedBitRateInf_field;
    iE_Extensions iE_Extensions_field;
};

typedef OssString TBCD_STRING;

typedef OssString PLMNidentity;

class OSS_PUBLIC __seq5;

class OSS_PUBLIC AuthorisedPLMNs : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq5 component;

    AuthorisedPLMNs();
    AuthorisedPLMNs(const AuthorisedPLMNs &);
    ~AuthorisedPLMNs();

    AuthorisedPLMNs & operator = (const AuthorisedPLMNs &);
    int operator == (const AuthorisedPLMNs &) const;
    int operator != (const AuthorisedPLMNs &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(AuthorisedPLMNs *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, AuthorisedPLMNs *);

    int remove_front();
    int remove_after(OssIndex);

    AuthorisedPLMNs *extract_after(OssIndex, OssIndex);
};

typedef __shared9 AuthorisedSNAs;

class OSS_PUBLIC __seq5   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef __shared9 authorisedSNAsList;
    typedef __shared4 iE_Extensions;

    __seq5();
    __seq5(const __seq5 &);
    __seq5(const pLMNidentity &, const authorisedSNAsList &, const iE_Extensions &);
    __seq5(const pLMNidentity &);

    __seq5 & operator = (const __seq5 &);
    int operator == (const __seq5 &) const;
    int operator != (const __seq5 &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    authorisedSNAsList *get_authorisedSNAsList();
    const authorisedSNAsList *get_authorisedSNAsList() const;
    void set_authorisedSNAsList(const authorisedSNAsList &);
    int authorisedSNAsList_is_present() const;
    void omit_authorisedSNAsList();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    authorisedSNAsList authorisedSNAsList_field;
    iE_Extensions iE_Extensions_field;
};

typedef OSS_UINT32 SNAC;

typedef OssString BindingID;

class OSS_PUBLIC BroadcastAssistanceDataDecipheringKeys   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString cipheringKeyFlag;
    typedef OssBitString currentDecipheringKey;
    typedef OssBitString nextDecipheringKey;

    BroadcastAssistanceDataDecipheringKeys();
    BroadcastAssistanceDataDecipheringKeys(const BroadcastAssistanceDataDecipheringKeys &);
    BroadcastAssistanceDataDecipheringKeys(const cipheringKeyFlag &, const currentDecipheringKey &, 
	const nextDecipheringKey &);

    BroadcastAssistanceDataDecipheringKeys & operator = (const BroadcastAssistanceDataDecipheringKeys &);
    int operator == (const BroadcastAssistanceDataDecipheringKeys &) const;
    int operator != (const BroadcastAssistanceDataDecipheringKeys &) const;

    cipheringKeyFlag & get_cipheringKeyFlag();
    const cipheringKeyFlag & get_cipheringKeyFlag() const;
    void set_cipheringKeyFlag(const cipheringKeyFlag &);

    currentDecipheringKey & get_currentDecipheringKey();
    const currentDecipheringKey & get_currentDecipheringKey() const;
    void set_currentDecipheringKey(const currentDecipheringKey &);

    nextDecipheringKey & get_nextDecipheringKey();
    const nextDecipheringKey & get_nextDecipheringKey() const;
    void set_nextDecipheringKey(const nextDecipheringKey &);
private:
    cipheringKeyFlag cipheringKeyFlag_field;
    currentDecipheringKey currentDecipheringKey_field;
    nextDecipheringKey nextDecipheringKey_field;
};

typedef OSS_UINT32 CauseRadioNetwork;

typedef OSS_UINT32 CauseTransmissionNetwork;

typedef OSS_UINT32 CauseNAS;

typedef OSS_UINT32 CauseProtocol;

typedef OSS_UINT32 CauseMisc;

typedef OSS_UINT32 CauseNon_Standard;

class OSS_PUBLIC Cause  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	radioNetwork_chosen = 1,
	transmissionNetwork_chosen = 2,
	nAS_chosen = 3,
	protocol_chosen = 4,
	misc_chosen = 5,
	non_Standard_chosen = 6
    };
    typedef OSS_UINT32 radioNetwork;
    typedef OSS_UINT32 transmissionNetwork;
    typedef OSS_UINT32 nAS;
    typedef OSS_UINT32 protocol;
    typedef OSS_UINT32 misc;
    typedef OSS_UINT32 non_Standard;

    Cause();
    Cause(const Cause &);

    Cause & operator = (const Cause &);
    int operator == (const Cause &) const;
    int operator != (const Cause &) const;

    radioNetwork *get_radioNetwork();
    const radioNetwork *get_radioNetwork() const;
    void set_radioNetwork(radioNetwork);

    transmissionNetwork *get_transmissionNetwork();
    const transmissionNetwork *get_transmissionNetwork() const;
    void set_transmissionNetwork(transmissionNetwork);

    nAS *get_nAS();
    const nAS *get_nAS() const;
    void set_nAS(nAS);

    protocol *get_protocol();
    const protocol *get_protocol() const;
    void set_protocol(protocol);

    misc *get_misc();
    const misc *get_misc() const;
    void set_misc(misc);

    non_Standard *get_non_Standard();
    const non_Standard *get_non_Standard() const;
    void set_non_Standard(non_Standard);
private:
    union {
	radioNetwork radioNetwork_field;
	transmissionNetwork transmissionNetwork_field;
	nAS nAS_field;
	protocol protocol_field;
	misc misc_field;
	non_Standard non_Standard_field;
    };
};

typedef OSS_INT32 Cell_Capacity_Class_Value;

typedef OSS_UINT32 LoadValue;

typedef OSS_UINT32 RTLoadValue;

typedef OSS_UINT32 NRTLoadInformationValue;

class OSS_PUBLIC CellLoadInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_INT32 cell_Capacity_Class_Value;
    typedef OSS_UINT32 loadValue;
    typedef OSS_UINT32 rTLoadValue;
    typedef OSS_UINT32 nRTLoadInformationValue;
    typedef __shared4 iE_Extensions;

    CellLoadInformation();
    CellLoadInformation(const CellLoadInformation &);
    CellLoadInformation(cell_Capacity_Class_Value, loadValue, rTLoadValue, nRTLoadInformationValue, 
	const iE_Extensions &);
    CellLoadInformation(cell_Capacity_Class_Value, loadValue);

    CellLoadInformation & operator = (const CellLoadInformation &);
    int operator == (const CellLoadInformation &) const;
    int operator != (const CellLoadInformation &) const;

    cell_Capacity_Class_Value & get_cell_Capacity_Class_Value();
    cell_Capacity_Class_Value get_cell_Capacity_Class_Value() const;
    void set_cell_Capacity_Class_Value(cell_Capacity_Class_Value);

    loadValue & get_loadValue();
    loadValue get_loadValue() const;
    void set_loadValue(loadValue);

    rTLoadValue *get_rTLoadValue();
    const rTLoadValue *get_rTLoadValue() const;
    void set_rTLoadValue(rTLoadValue);
    int rTLoadValue_is_present() const;
    void omit_rTLoadValue();

    nRTLoadInformationValue *get_nRTLoadInformationValue();
    const nRTLoadInformationValue *get_nRTLoadInformationValue() const;
    void set_nRTLoadInformationValue(nRTLoadInformationValue);
    int nRTLoadInformationValue_is_present() const;
    void omit_nRTLoadInformationValue();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    cell_Capacity_Class_Value cell_Capacity_Class_Value_field;
    loadValue loadValue_field;
    rTLoadValue rTLoadValue_field;
    nRTLoadInformationValue nRTLoadInformationValue_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SourceUTRANCellID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OSS_UINT32 uTRANcellID;
    typedef __shared4 iE_Extensions;

    SourceUTRANCellID();
    SourceUTRANCellID(const SourceUTRANCellID &);
    SourceUTRANCellID(const pLMNidentity &, uTRANcellID, const iE_Extensions &);
    SourceUTRANCellID(const pLMNidentity &, uTRANcellID);

    SourceUTRANCellID & operator = (const SourceUTRANCellID &);
    int operator == (const SourceUTRANCellID &) const;
    int operator != (const SourceUTRANCellID &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    uTRANcellID & get_uTRANcellID();
    uTRANcellID get_uTRANcellID() const;
    void set_uTRANcellID(uTRANcellID);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    uTRANcellID uTRANcellID_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC CGI   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OssString lAC;
    typedef OssString cI;
    typedef __shared4 iE_Extensions;

    CGI();
    CGI(const CGI &);
    CGI(const pLMNidentity &, const lAC &, const cI &, const iE_Extensions &);
    CGI(const pLMNidentity &, const lAC &, const cI &);

    CGI & operator = (const CGI &);
    int operator == (const CGI &) const;
    int operator != (const CGI &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    lAC & get_lAC();
    const lAC & get_lAC() const;
    void set_lAC(const lAC &);

    cI & get_cI();
    const cI & get_cI() const;
    void set_cI(const cI &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    lAC lAC_field;
    cI cI_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SourceCellID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	sourceUTRANCellID_chosen = 1,
	sourceGERANCellID_chosen = 2
    };
    typedef SourceUTRANCellID sourceUTRANCellID;
    typedef CGI sourceGERANCellID;

    SourceCellID();
    SourceCellID(const SourceCellID &);
    ~SourceCellID();

    SourceCellID & operator = (const SourceCellID &);
    int operator == (const SourceCellID &) const;
    int operator != (const SourceCellID &) const;

    sourceUTRANCellID *get_sourceUTRANCellID();
    const sourceUTRANCellID *get_sourceUTRANCellID() const;
    void set_sourceUTRANCellID(const sourceUTRANCellID &);

    sourceGERANCellID *get_sourceGERANCellID();
    const sourceGERANCellID *get_sourceGERANCellID() const;
    void set_sourceGERANCellID(const sourceGERANCellID &);
private:
    union {
	sourceUTRANCellID *sourceUTRANCellID_field;
	sourceGERANCellID *sourceGERANCellID_field;
    };
    void cleanup();
};

class OSS_PUBLIC CellLoadInformationGroup   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef SourceCellID sourceCellID;
    typedef CellLoadInformation uplinkCellLoadInformation;
    typedef CellLoadInformation downlinkCellLoadInformation;
    typedef __shared4 iE_Extensions;

    CellLoadInformationGroup();
    CellLoadInformationGroup(const CellLoadInformationGroup &);
    CellLoadInformationGroup(const sourceCellID &, const uplinkCellLoadInformation &, 
	const downlinkCellLoadInformation &, const iE_Extensions &);
    CellLoadInformationGroup(const sourceCellID &);

    CellLoadInformationGroup & operator = (const CellLoadInformationGroup &);
    int operator == (const CellLoadInformationGroup &) const;
    int operator != (const CellLoadInformationGroup &) const;

    sourceCellID & get_sourceCellID();
    const sourceCellID & get_sourceCellID() const;
    void set_sourceCellID(const sourceCellID &);

    uplinkCellLoadInformation *get_uplinkCellLoadInformation();
    const uplinkCellLoadInformation *get_uplinkCellLoadInformation() const;
    void set_uplinkCellLoadInformation(const uplinkCellLoadInformation &);
    int uplinkCellLoadInformation_is_present() const;
    void omit_uplinkCellLoadInformation();

    downlinkCellLoadInformation *get_downlinkCellLoadInformation();
    const downlinkCellLoadInformation *get_downlinkCellLoadInformation() const;
    void set_downlinkCellLoadInformation(const downlinkCellLoadInformation &);
    int downlinkCellLoadInformation_is_present() const;
    void omit_downlinkCellLoadInformation();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    sourceCellID sourceCellID_field;
    uplinkCellLoadInformation uplinkCellLoadInformation_field;
    downlinkCellLoadInformation downlinkCellLoadInformation_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq10;

class OSS_PUBLIC __shared27 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq10 component;

    __shared27();
    __shared27(const __shared27 &);
    ~__shared27();

    __shared27 & operator = (const __shared27 &);
    int operator == (const __shared27 &) const;
    int operator != (const __shared27 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared27 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared27 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared27 *extract_after(OssIndex, OssIndex);
};

typedef __shared27 CriticalityDiagnostics_IE_List;

class OSS_PUBLIC CriticalityDiagnostics   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 procedureCode;
    typedef enum TriggeringMessage triggeringMessage;
    typedef enum Criticality procedureCriticality;
    typedef __shared27 iEsCriticalityDiagnostics;
    typedef __shared4 iE_Extensions;

    CriticalityDiagnostics();
    CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics(procedureCode, triggeringMessage, procedureCriticality, 
	const iEsCriticalityDiagnostics &, const iE_Extensions &);

    CriticalityDiagnostics & operator = (const CriticalityDiagnostics &);
    int operator == (const CriticalityDiagnostics &) const;
    int operator != (const CriticalityDiagnostics &) const;

    procedureCode *get_procedureCode();
    const procedureCode *get_procedureCode() const;
    void set_procedureCode(procedureCode);
    int procedureCode_is_present() const;
    void omit_procedureCode();

    triggeringMessage *get_triggeringMessage();
    const triggeringMessage *get_triggeringMessage() const;
    void set_triggeringMessage(triggeringMessage);
    int triggeringMessage_is_present() const;
    void omit_triggeringMessage();

    procedureCriticality *get_procedureCriticality();
    const procedureCriticality *get_procedureCriticality() const;
    void set_procedureCriticality(procedureCriticality);
    int procedureCriticality_is_present() const;
    void omit_procedureCriticality();

    iEsCriticalityDiagnostics *get_iEsCriticalityDiagnostics();
    const iEsCriticalityDiagnostics *get_iEsCriticalityDiagnostics() const;
    void set_iEsCriticalityDiagnostics(const iEsCriticalityDiagnostics &);
    int iEsCriticalityDiagnostics_is_present() const;
    void omit_iEsCriticalityDiagnostics();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    procedureCode procedureCode_field;
    triggeringMessage triggeringMessage_field;
    procedureCriticality procedureCriticality_field;
    iEsCriticalityDiagnostics iEsCriticalityDiagnostics_field;
    iE_Extensions iE_Extensions_field;
};

typedef OSS_UINT32 RepetitionNumber0;

class OSS_PUBLIC __seq12;

class OSS_PUBLIC MessageStructure : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq12 component;

    MessageStructure();
    MessageStructure(const MessageStructure &);
    ~MessageStructure();

    MessageStructure & operator = (const MessageStructure &);
    int operator == (const MessageStructure &) const;
    int operator != (const MessageStructure &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(MessageStructure *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, MessageStructure *);

    int remove_front();
    int remove_after(OssIndex);

    MessageStructure *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC CriticalityDiagnostics_IE_List_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    CriticalityDiagnostics_IE_List_ExtIEs_Extension();
    CriticalityDiagnostics_IE_List_ExtIEs_Extension(const CriticalityDiagnostics_IE_List_ExtIEs_Extension &);
    ~CriticalityDiagnostics_IE_List_ExtIEs_Extension();
    CriticalityDiagnostics_IE_List_ExtIEs_Extension & operator = (const CriticalityDiagnostics_IE_List_ExtIEs_Extension &);
    int operator == (const CriticalityDiagnostics_IE_List_ExtIEs_Extension &) const;
    int operator != (const CriticalityDiagnostics_IE_List_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    MessageStructure *get_MessageStructure();
    const MessageStructure *get_MessageStructure() const;
    void set_MessageStructure(const MessageStructure &);
    MessageStructure *release_MessageStructure();
    void set_MessageStructure(MessageStructure *);

    TypeOfError *get_TypeOfError();
    const TypeOfError *get_TypeOfError() const;
    void set_TypeOfError(const TypeOfError &);
    TypeOfError *release_TypeOfError();
    void set_TypeOfError(TypeOfError *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq9;

class OSS_PUBLIC __seqof8 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq9 component;

    __seqof8();
    __seqof8(const __seqof8 &);
    ~__seqof8();

    __seqof8 & operator = (const __seqof8 &);
    int operator == (const __seqof8 &) const;
    int operator != (const __seqof8 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof8 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof8 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof8 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq10   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum Criticality iECriticality;
    typedef OSS_UINT32 iE_ID;
    typedef OSS_UINT32 repetitionNumber;
    typedef __seqof8 iE_Extensions;

    __seq10();
    __seq10(const __seq10 &);
    __seq10(iECriticality, iE_ID, repetitionNumber, const iE_Extensions &);
    __seq10(iECriticality, iE_ID);

    __seq10 & operator = (const __seq10 &);
    int operator == (const __seq10 &) const;
    int operator != (const __seq10 &) const;

    iECriticality & get_iECriticality();
    iECriticality get_iECriticality() const;
    void set_iECriticality(iECriticality);

    iE_ID & get_iE_ID();
    iE_ID get_iE_ID() const;
    void set_iE_ID(iE_ID);

    repetitionNumber *get_repetitionNumber();
    const repetitionNumber *get_repetitionNumber() const;
    void set_repetitionNumber(repetitionNumber);
    int repetitionNumber_is_present() const;
    void omit_repetitionNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    iECriticality iECriticality_field;
    iE_ID iE_ID_field;
    repetitionNumber repetitionNumber_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq9   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CriticalityDiagnostics_IE_List_ExtIEs_Extension extensionValue;

    __seq9();
    __seq9(const __seq9 &);
    __seq9(id, criticality, const extensionValue &);

    __seq9 & operator = (const __seq9 &);
    int operator == (const __seq9 &) const;
    int operator != (const __seq9 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

typedef OSS_UINT32 RepetitionNumber1;

class OSS_PUBLIC __seq12   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 iE_ID;
    typedef OSS_UINT32 repetitionNumber;
    typedef __shared4 iE_Extensions;

    __seq12();
    __seq12(const __seq12 &);
    __seq12(iE_ID, repetitionNumber, const iE_Extensions &);
    __seq12(iE_ID);

    __seq12 & operator = (const __seq12 &);
    int operator == (const __seq12 &) const;
    int operator != (const __seq12 &) const;

    iE_ID & get_iE_ID();
    iE_ID get_iE_ID() const;
    void set_iE_ID(iE_ID);

    repetitionNumber *get_repetitionNumber();
    const repetitionNumber *get_repetitionNumber() const;
    void set_repetitionNumber(repetitionNumber);
    int repetitionNumber_is_present() const;
    void omit_repetitionNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    iE_ID iE_ID_field;
    repetitionNumber repetitionNumber_field;
    iE_Extensions iE_Extensions_field;
};

typedef OssString LAC;

typedef OssString CI;

typedef OSS_UINT32 CN_ID;

typedef OSS_UINT32 DataVolumeReference;

typedef OSS_UINT32 DCH_ID;

typedef OSS_UINT32 DL_GTP_PDU_SequenceNumber;

typedef OSS_UINT32 DL_N_PDU_SequenceNumber;

typedef OSS_UINT32 D_RNTI;

typedef OSS_UINT32 DSCH_ID;

typedef OssBitString EncryptionKey;

typedef __shared9 PermittedIntegrityProtectionAlgorithms;

class OSS_PUBLIC __shared15   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared9 permittedAlgorithms;
    typedef OssBitString key;
    typedef __shared4 iE_Extensions;

    __shared15();
    __shared15(const __shared15 &);
    __shared15(const permittedAlgorithms &, const key &, const iE_Extensions &);
    __shared15(const permittedAlgorithms &, const key &);

    __shared15 & operator = (const __shared15 &);
    int operator == (const __shared15 &) const;
    int operator != (const __shared15 &) const;

    permittedAlgorithms & get_permittedAlgorithms();
    const permittedAlgorithms & get_permittedAlgorithms() const;
    void set_permittedAlgorithms(const permittedAlgorithms &);

    key & get_key();
    const key & get_key() const;
    void set_key(const key &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    permittedAlgorithms permittedAlgorithms_field;
    key key_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared15 IntegrityProtectionInformation;

typedef __shared15 EncryptionInformation;

class OSS_PUBLIC __shared26 : public OssList  /* SEQUENCE OF */
{
public:
    typedef OssString component;

    __shared26();
    __shared26(const __shared26 &);
    ~__shared26();

    __shared26 & operator = (const __shared26 &);
    int operator == (const __shared26 &) const;
    int operator != (const __shared26 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared26 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared26 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared26 *extract_after(OssIndex, OssIndex);
};

typedef __shared26 PositioningDataSet;

typedef __shared26 IMEIList;

typedef __shared26 IMEISVList;

class OSS_PUBLIC IMEIGroup   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString iMEI;
    typedef OssBitString iMEIMask;
    typedef __shared4 iE_Extensions;

    IMEIGroup();
    IMEIGroup(const IMEIGroup &);
    IMEIGroup(const iMEI &, const iMEIMask &, const iE_Extensions &);
    IMEIGroup(const iMEI &, const iMEIMask &);

    IMEIGroup & operator = (const IMEIGroup &);
    int operator == (const IMEIGroup &) const;
    int operator != (const IMEIGroup &) const;

    iMEI & get_iMEI();
    const iMEI & get_iMEI() const;
    void set_iMEI(const iMEI &);

    iMEIMask & get_iMEIMask();
    const iMEIMask & get_iMEIMask() const;
    void set_iMEIMask(const iMEIMask &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    iMEI iMEI_field;
    iMEIMask iMEIMask_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC IMEISVGroup   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString iMEISV;
    typedef OssBitString iMEISVMask;
    typedef __shared4 iE_Extensions;

    IMEISVGroup();
    IMEISVGroup(const IMEISVGroup &);
    IMEISVGroup(const iMEISV &, const iMEISVMask &, const iE_Extensions &);
    IMEISVGroup(const iMEISV &, const iMEISVMask &);

    IMEISVGroup & operator = (const IMEISVGroup &);
    int operator == (const IMEISVGroup &) const;
    int operator != (const IMEISVGroup &) const;

    iMEISV & get_iMEISV();
    const iMEISV & get_iMEISV() const;
    void set_iMEISV(const iMEISV &);

    iMEISVMask & get_iMEISVMask();
    const iMEISVMask & get_iMEISVMask() const;
    void set_iMEISVMask(const iMEISVMask &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    iMEISV iMEISV_field;
    iMEISVMask iMEISVMask_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC EquipmentsToBeTraced  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	iMEIlist_chosen = 1,
	iMEISVlist_chosen = 2,
	iMEIgroup_chosen = 3,
	iMEISVgroup_chosen = 4
    };
    typedef __shared26 iMEIlist;
    typedef __shared26 iMEISVlist;
    typedef IMEIGroup iMEIgroup;
    typedef IMEISVGroup iMEISVgroup;

    EquipmentsToBeTraced();
    EquipmentsToBeTraced(const EquipmentsToBeTraced &);
    ~EquipmentsToBeTraced();

    EquipmentsToBeTraced & operator = (const EquipmentsToBeTraced &);
    int operator == (const EquipmentsToBeTraced &) const;
    int operator != (const EquipmentsToBeTraced &) const;

    iMEIlist *get_iMEIlist();
    const iMEIlist *get_iMEIlist() const;
    void set_iMEIlist(const iMEIlist &);

    iMEISVlist *get_iMEISVlist();
    const iMEISVlist *get_iMEISVlist() const;
    void set_iMEISVlist(const iMEISVlist &);

    iMEIgroup *get_iMEIgroup();
    const iMEIgroup *get_iMEIgroup() const;
    void set_iMEIgroup(const iMEIgroup &);

    iMEISVgroup *get_iMEISVgroup();
    const iMEISVgroup *get_iMEISVgroup() const;
    void set_iMEISVgroup(const iMEISVgroup &);
private:
    union {
	void *iMEIlist_field;
	void *iMEISVlist_field;
	iMEIgroup *iMEIgroup_field;
	iMEISVgroup *iMEISVgroup_field;
    };
    void cleanup();
};

class OSS_PUBLIC LAI   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OssString lAC;
    typedef __shared4 iE_Extensions;

    LAI();
    LAI(const LAI &);
    LAI(const pLMNidentity &, const lAC &, const iE_Extensions &);
    LAI(const pLMNidentity &, const lAC &);

    LAI & operator = (const LAI &);
    int operator == (const LAI &) const;
    int operator != (const LAI &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    lAC & get_lAC();
    const lAC & get_lAC() const;
    void set_lAC(const lAC &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    lAC lAC_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GERAN_Cell_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef LAI lAI;
    typedef OssString rAC;
    typedef OssString cI;
    typedef __shared4 iE_Extensions;

    GERAN_Cell_ID();
    GERAN_Cell_ID(const GERAN_Cell_ID &);
    GERAN_Cell_ID(const lAI &, const rAC &, const cI &, const iE_Extensions &);
    GERAN_Cell_ID(const lAI &, const rAC &, const cI &);

    GERAN_Cell_ID & operator = (const GERAN_Cell_ID &);
    int operator == (const GERAN_Cell_ID &) const;
    int operator != (const GERAN_Cell_ID &) const;

    lAI & get_lAI();
    const lAI & get_lAI() const;
    void set_lAI(const lAI &);

    rAC & get_rAC();
    const rAC & get_rAC() const;
    void set_rAC(const rAC &);

    cI & get_cI();
    const cI & get_cI() const;
    void set_cI(const cI &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    lAI lAI_field;
    rAC rAC_field;
    cI cI_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GlobalCN_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OSS_UINT32 cN_ID;

    GlobalCN_ID();
    GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID(const pLMNidentity &, cN_ID);

    GlobalCN_ID & operator = (const GlobalCN_ID &);
    int operator == (const GlobalCN_ID &) const;
    int operator != (const GlobalCN_ID &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    cN_ID & get_cN_ID();
    cN_ID get_cN_ID() const;
    void set_cN_ID(cN_ID);
private:
    pLMNidentity pLMNidentity_field;
    cN_ID cN_ID_field;
};

typedef OSS_UINT32 RNC_ID;

class OSS_PUBLIC GlobalRNC_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OSS_UINT32 rNC_ID;

    GlobalRNC_ID();
    GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID(const pLMNidentity &, rNC_ID);

    GlobalRNC_ID & operator = (const GlobalRNC_ID &);
    int operator == (const GlobalRNC_ID &) const;
    int operator != (const GlobalRNC_ID &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    rNC_ID & get_rNC_ID();
    rNC_ID get_rNC_ID() const;
    void set_rNC_ID(rNC_ID);
private:
    pLMNidentity pLMNidentity_field;
    rNC_ID rNC_ID_field;
};

typedef OssString GTP_TEI;

typedef OssString IMEI;

typedef OssString IMEISV;

typedef OssString IMSI;

class OSS_PUBLIC RNCTraceInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString traceReference;
    typedef enum _enum4 traceActivationIndicator;
    typedef EquipmentsToBeTraced equipmentsToBeTraced;
    typedef __shared4 iE_Extensions;

    RNCTraceInformation();
    RNCTraceInformation(const RNCTraceInformation &);
    RNCTraceInformation(const traceReference &, traceActivationIndicator, const equipmentsToBeTraced &, 
	const iE_Extensions &);
    RNCTraceInformation(const traceReference &, traceActivationIndicator);

    RNCTraceInformation & operator = (const RNCTraceInformation &);
    int operator == (const RNCTraceInformation &) const;
    int operator != (const RNCTraceInformation &) const;

    traceReference & get_traceReference();
    const traceReference & get_traceReference() const;
    void set_traceReference(const traceReference &);

    traceActivationIndicator & get_traceActivationIndicator();
    traceActivationIndicator get_traceActivationIndicator() const;
    void set_traceActivationIndicator(traceActivationIndicator);

    equipmentsToBeTraced *get_equipmentsToBeTraced();
    const equipmentsToBeTraced *get_equipmentsToBeTraced() const;
    void set_equipmentsToBeTraced(const equipmentsToBeTraced &);
    int equipmentsToBeTraced_is_present() const;
    void omit_equipmentsToBeTraced();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    traceReference traceReference_field;
    traceActivationIndicator traceActivationIndicator_field;
    equipmentsToBeTraced equipmentsToBeTraced_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC InformationTransferType  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	rNCTraceInformation_chosen = 1
    };
    typedef RNCTraceInformation rNCTraceInformation;

    InformationTransferType();
    InformationTransferType(const InformationTransferType &);
    ~InformationTransferType();

    InformationTransferType & operator = (const InformationTransferType &);
    int operator == (const InformationTransferType &) const;
    int operator != (const InformationTransferType &) const;

    rNCTraceInformation *get_rNCTraceInformation();
    const rNCTraceInformation *get_rNCTraceInformation() const;
    void set_rNCTraceInformation(const rNCTraceInformation &);
private:
    union {
	rNCTraceInformation *rNCTraceInformation_field;
    };
    void cleanup();
};

typedef OssBitString IntegrityProtectionKey;

class OSS_PUBLIC RIMRoutingAddress  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	globalRNC_ID_chosen = 1,
	gERAN_Cell_ID_chosen = 2
    };
    typedef GlobalRNC_ID globalRNC_ID;
    typedef GERAN_Cell_ID gERAN_Cell_ID;

    RIMRoutingAddress();
    RIMRoutingAddress(const RIMRoutingAddress &);
    ~RIMRoutingAddress();

    RIMRoutingAddress & operator = (const RIMRoutingAddress &);
    int operator == (const RIMRoutingAddress &) const;
    int operator != (const RIMRoutingAddress &) const;

    globalRNC_ID *get_globalRNC_ID();
    const globalRNC_ID *get_globalRNC_ID() const;
    void set_globalRNC_ID(const globalRNC_ID &);

    gERAN_Cell_ID *get_gERAN_Cell_ID();
    const gERAN_Cell_ID *get_gERAN_Cell_ID() const;
    void set_gERAN_Cell_ID(const gERAN_Cell_ID &);
private:
    union {
	globalRNC_ID *globalRNC_ID_field;
	gERAN_Cell_ID *gERAN_Cell_ID_field;
    };
    void cleanup();
};

class OSS_PUBLIC RIM_Transfer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString rIMInformation;
    typedef RIMRoutingAddress rIMRoutingAddress;
    typedef __shared4 iE_Extensions;

    RIM_Transfer();
    RIM_Transfer(const RIM_Transfer &);
    RIM_Transfer(const rIMInformation &, const rIMRoutingAddress &, const iE_Extensions &);
    RIM_Transfer(const rIMInformation &);

    RIM_Transfer & operator = (const RIM_Transfer &);
    int operator == (const RIM_Transfer &) const;
    int operator != (const RIM_Transfer &) const;

    rIMInformation & get_rIMInformation();
    const rIMInformation & get_rIMInformation() const;
    void set_rIMInformation(const rIMInformation &);

    rIMRoutingAddress *get_rIMRoutingAddress();
    const rIMRoutingAddress *get_rIMRoutingAddress() const;
    void set_rIMRoutingAddress(const rIMRoutingAddress &);
    int rIMRoutingAddress_is_present() const;
    void omit_rIMRoutingAddress();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rIMInformation rIMInformation_field;
    rIMRoutingAddress rIMRoutingAddress_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC InterSystemInformationTransferType  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	rIM_Transfer_chosen = 1
    };
    typedef RIM_Transfer rIM_Transfer;

    InterSystemInformationTransferType();
    InterSystemInformationTransferType(const InterSystemInformationTransferType &);
    ~InterSystemInformationTransferType();

    InterSystemInformationTransferType & operator = (const InterSystemInformationTransferType &);
    int operator == (const InterSystemInformationTransferType &) const;
    int operator != (const InterSystemInformationTransferType &) const;

    rIM_Transfer *get_rIM_Transfer();
    const rIM_Transfer *get_rIM_Transfer() const;
    void set_rIM_Transfer(const rIM_Transfer &);
private:
    union {
	rIM_Transfer *rIM_Transfer_field;
    };
    void cleanup();
};

class OSS_PUBLIC InterSystemInformation_TransparentContainer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef CellLoadInformation downlinkCellLoadInformation;
    typedef CellLoadInformation uplinkCellLoadInformation;
    typedef __shared4 iE_Extensions;

    InterSystemInformation_TransparentContainer();
    InterSystemInformation_TransparentContainer(const InterSystemInformation_TransparentContainer &);
    InterSystemInformation_TransparentContainer(const downlinkCellLoadInformation &, 
	const uplinkCellLoadInformation &, const iE_Extensions &);

    InterSystemInformation_TransparentContainer & operator = (const InterSystemInformation_TransparentContainer &);
    int operator == (const InterSystemInformation_TransparentContainer &) const;
    int operator != (const InterSystemInformation_TransparentContainer &) const;

    downlinkCellLoadInformation *get_downlinkCellLoadInformation();
    const downlinkCellLoadInformation *get_downlinkCellLoadInformation() const;
    void set_downlinkCellLoadInformation(const downlinkCellLoadInformation &);
    int downlinkCellLoadInformation_is_present() const;
    void omit_downlinkCellLoadInformation();

    uplinkCellLoadInformation *get_uplinkCellLoadInformation();
    const uplinkCellLoadInformation *get_uplinkCellLoadInformation() const;
    void set_uplinkCellLoadInformation(const uplinkCellLoadInformation &);
    int uplinkCellLoadInformation_is_present() const;
    void omit_uplinkCellLoadInformation();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    downlinkCellLoadInformation downlinkCellLoadInformation_field;
    uplinkCellLoadInformation uplinkCellLoadInformation_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq31;

class OSS_PUBLIC LA_LIST : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq31 component;

    LA_LIST();
    LA_LIST(const LA_LIST &);
    ~LA_LIST();

    LA_LIST & operator = (const LA_LIST &);
    int operator == (const LA_LIST &) const;
    int operator != (const LA_LIST &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(LA_LIST *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, LA_LIST *);

    int remove_front();
    int remove_after(OssIndex);

    LA_LIST *extract_after(OssIndex, OssIndex);
};

typedef __shared9 ListOF_SNAs;

class OSS_PUBLIC __seq31   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString lAC;
    typedef __shared9 listOF_SNAs;
    typedef __shared4 iE_Extensions;

    __seq31();
    __seq31(const __seq31 &);
    __seq31(const lAC &, const listOF_SNAs &, const iE_Extensions &);
    __seq31(const lAC &, const listOF_SNAs &);

    __seq31 & operator = (const __seq31 &);
    int operator == (const __seq31 &) const;
    int operator != (const __seq31 &) const;

    lAC & get_lAC();
    const lAC & get_lAC() const;
    void set_lAC(const lAC &);

    listOF_SNAs & get_listOF_SNAs();
    const listOF_SNAs & get_listOF_SNAs() const;
    void set_listOF_SNAs(const listOF_SNAs &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    lAC lAC_field;
    listOF_SNAs listOF_SNAs_field;
    iE_Extensions iE_Extensions_field;
};

typedef OssString SAC;

class OSS_PUBLIC LastKnownServiceArea   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef SAI sAI;
    typedef OSS_UINT32 ageOfSAI;
    typedef __shared4 iE_Extensions;

    LastKnownServiceArea();
    LastKnownServiceArea(const LastKnownServiceArea &);
    LastKnownServiceArea(const sAI &, ageOfSAI, const iE_Extensions &);
    LastKnownServiceArea(const sAI &, ageOfSAI);

    LastKnownServiceArea & operator = (const LastKnownServiceArea &);
    int operator == (const LastKnownServiceArea &) const;
    int operator != (const LastKnownServiceArea &) const;

    sAI & get_sAI();
    const sAI & get_sAI() const;
    void set_sAI(const sAI &);

    ageOfSAI & get_ageOfSAI();
    ageOfSAI get_ageOfSAI() const;
    void set_ageOfSAI(ageOfSAI);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    sAI sAI_field;
    ageOfSAI ageOfSAI_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC InterfacesToTraceItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum _enum3 asn1_interface;
    typedef __shared4 iE_Extensions;

    InterfacesToTraceItem();
    InterfacesToTraceItem(const InterfacesToTraceItem &);
    InterfacesToTraceItem(asn1_interface, const iE_Extensions &);
    InterfacesToTraceItem(asn1_interface);

    InterfacesToTraceItem & operator = (const InterfacesToTraceItem &);
    int operator == (const InterfacesToTraceItem &) const;
    int operator != (const InterfacesToTraceItem &) const;

    asn1_interface & get_asn1_interface();
    asn1_interface get_asn1_interface() const;
    void set_asn1_interface(asn1_interface);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    asn1_interface asn1_interface_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC ListOfInterfacesToTrace : public OssList  /* SEQUENCE OF */
{
public:
    typedef InterfacesToTraceItem component;

    ListOfInterfacesToTrace();
    ListOfInterfacesToTrace(const ListOfInterfacesToTrace &);
    ~ListOfInterfacesToTrace();

    ListOfInterfacesToTrace & operator = (const ListOfInterfacesToTrace &);
    int operator == (const ListOfInterfacesToTrace &) const;
    int operator != (const ListOfInterfacesToTrace &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(ListOfInterfacesToTrace *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, ListOfInterfacesToTrace *);

    int remove_front();
    int remove_after(OssIndex);

    ListOfInterfacesToTrace *extract_after(OssIndex, OssIndex);
};

typedef OssString RequestedGPSAssistanceData;

class OSS_PUBLIC LocationRelatedDataRequestType   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum RequestedLocationRelatedDataType requestedLocationRelatedDataType;
    typedef OssString requestedGPSAssistanceData;

    LocationRelatedDataRequestType();
    LocationRelatedDataRequestType(const LocationRelatedDataRequestType &);
    LocationRelatedDataRequestType(requestedLocationRelatedDataType, const requestedGPSAssistanceData &);
    LocationRelatedDataRequestType(requestedLocationRelatedDataType);

    LocationRelatedDataRequestType & operator = (const LocationRelatedDataRequestType &);
    int operator == (const LocationRelatedDataRequestType &) const;
    int operator != (const LocationRelatedDataRequestType &) const;

    requestedLocationRelatedDataType & get_requestedLocationRelatedDataType();
    requestedLocationRelatedDataType get_requestedLocationRelatedDataType() const;
    void set_requestedLocationRelatedDataType(requestedLocationRelatedDataType);

    requestedGPSAssistanceData *get_requestedGPSAssistanceData();
    const requestedGPSAssistanceData *get_requestedGPSAssistanceData() const;
    void set_requestedGPSAssistanceData(const requestedGPSAssistanceData &);
    int requestedGPSAssistanceData_is_present() const;
    void omit_requestedGPSAssistanceData();
private:
    OSS_UINT32 bit_mask;
    requestedLocationRelatedDataType requestedLocationRelatedDataType_field;
    requestedGPSAssistanceData requestedGPSAssistanceData_field;
};

typedef OSS_UINT32 MaxSDU_Size;

typedef OssBitString NAS_SynchronisationIndicator;

typedef OSS_UINT32 NumberOfIuInstances;

class OSS_PUBLIC RAI   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef LAI lAI;
    typedef OssString rAC;
    typedef __shared4 iE_Extensions;

    RAI();
    RAI(const RAI &);
    RAI(const lAI &, const rAC &, const iE_Extensions &);
    RAI(const lAI &, const rAC &);

    RAI & operator = (const RAI &);
    int operator == (const RAI &) const;
    int operator != (const RAI &) const;

    lAI & get_lAI();
    const lAI & get_lAI() const;
    void set_lAI(const lAI &);

    rAC & get_rAC();
    const rAC & get_rAC() const;
    void set_rAC(const rAC &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    lAI lAI_field;
    rAC rAC_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC PagingAreaID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	lAI_chosen = 1,
	rAI_chosen = 2
    };
    typedef LAI lAI;
    typedef RAI rAI;

    PagingAreaID();
    PagingAreaID(const PagingAreaID &);
    ~PagingAreaID();

    PagingAreaID & operator = (const PagingAreaID &);
    int operator == (const PagingAreaID &) const;
    int operator != (const PagingAreaID &) const;

    lAI *get_lAI();
    const lAI *get_lAI() const;
    void set_lAI(const lAI &);

    rAI *get_rAI();
    const rAI *get_rAI() const;
    void set_rAI(const rAI &);
private:
    union {
	lAI *lAI_field;
	rAI *rAI_field;
    };
    void cleanup();
};

class OSS_PUBLIC PermanentNAS_UE_ID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	iMSI_chosen = 1
    };
    typedef OssString iMSI;

    PermanentNAS_UE_ID();
    PermanentNAS_UE_ID(const PermanentNAS_UE_ID &);
    ~PermanentNAS_UE_ID();

    PermanentNAS_UE_ID & operator = (const PermanentNAS_UE_ID &);
    int operator == (const PermanentNAS_UE_ID &) const;
    int operator != (const PermanentNAS_UE_ID &) const;

    iMSI *get_iMSI();
    const iMSI *get_iMSI() const;
    void set_iMSI(const iMSI &);
private:
    union {
	OSSC::COssString iMSI_field;
    };
    void cleanup();
};

typedef __shared9 PermittedEncryptionAlgorithms;

class OSS_PUBLIC __seq36;

class OSS_PUBLIC PLMNs_in_shared_network : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq36 component;

    PLMNs_in_shared_network();
    PLMNs_in_shared_network(const PLMNs_in_shared_network &);
    ~PLMNs_in_shared_network();

    PLMNs_in_shared_network & operator = (const PLMNs_in_shared_network &);
    int operator == (const PLMNs_in_shared_network &) const;
    int operator != (const PLMNs_in_shared_network &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(PLMNs_in_shared_network *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, PLMNs_in_shared_network *);

    int remove_front();
    int remove_after(OssIndex);

    PLMNs_in_shared_network *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq36   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef LA_LIST lA_LIST;
    typedef __shared4 iE_Extensions;

    __seq36();
    __seq36(const __seq36 &);
    __seq36(const pLMNidentity &, const lA_LIST &, const iE_Extensions &);
    __seq36(const pLMNidentity &, const lA_LIST &);

    __seq36 & operator = (const __seq36 &);
    int operator == (const __seq36 &) const;
    int operator != (const __seq36 &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    lA_LIST & get_lA_LIST();
    const lA_LIST & get_lA_LIST() const;
    void set_lA_LIST(const lA_LIST &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    lA_LIST lA_LIST_field;
    iE_Extensions iE_Extensions_field;
};

typedef OssBitString PositioningDataDiscriminator;

typedef OssString PositioningMethodAndUsage;

class OSS_PUBLIC PositionData   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString positioningDataDiscriminator;
    typedef __shared26 positioningDataSet;
    typedef __shared4 iE_Extensions;

    PositionData();
    PositionData(const PositionData &);
    PositionData(const positioningDataDiscriminator &, const positioningDataSet &, 
	const iE_Extensions &);
    PositionData(const positioningDataDiscriminator &);

    PositionData & operator = (const PositionData &);
    int operator == (const PositionData &) const;
    int operator != (const PositionData &) const;

    positioningDataDiscriminator & get_positioningDataDiscriminator();
    const positioningDataDiscriminator & get_positioningDataDiscriminator() const;
    void set_positioningDataDiscriminator(const positioningDataDiscriminator &);

    positioningDataSet *get_positioningDataSet();
    const positioningDataSet *get_positioningDataSet() const;
    void set_positioningDataSet(const positioningDataSet &);
    int positioningDataSet_is_present() const;
    void omit_positioningDataSet();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    positioningDataDiscriminator positioningDataDiscriminator_field;
    positioningDataSet positioningDataSet_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC Shared_Network_Information   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef PLMNs_in_shared_network pLMNs_in_shared_network;
    typedef __shared4 iE_Extensions;

    Shared_Network_Information();
    Shared_Network_Information(const Shared_Network_Information &);
    Shared_Network_Information(const pLMNs_in_shared_network &, const iE_Extensions &);
    Shared_Network_Information(const pLMNs_in_shared_network &);

    Shared_Network_Information & operator = (const Shared_Network_Information &);
    int operator == (const Shared_Network_Information &) const;
    int operator != (const Shared_Network_Information &) const;

    pLMNs_in_shared_network & get_pLMNs_in_shared_network();
    const pLMNs_in_shared_network & get_pLMNs_in_shared_network() const;
    void set_pLMNs_in_shared_network(const pLMNs_in_shared_network &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNs_in_shared_network pLMNs_in_shared_network_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC ProvidedData  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	shared_network_information_chosen = 1
    };
    typedef Shared_Network_Information shared_network_information;

    ProvidedData();
    ProvidedData(const ProvidedData &);
    ~ProvidedData();

    ProvidedData & operator = (const ProvidedData &);
    int operator == (const ProvidedData &) const;
    int operator != (const ProvidedData &) const;

    shared_network_information *get_shared_network_information();
    const shared_network_information *get_shared_network_information() const;
    void set_shared_network_information(const shared_network_information &);
private:
    union {
	shared_network_information *shared_network_information_field;
    };
    void cleanup();
};

typedef OssString P_TMSI;

typedef OssBitString RAB_ID;

typedef OSS_UINT32 TransferDelay;

typedef OSS_UINT32 TrafficHandlingPriority;

class OSS_PUBLIC RAB_Parameters_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_Parameters_ExtIEs_Extension();
    RAB_Parameters_ExtIEs_Extension(const RAB_Parameters_ExtIEs_Extension &);
    ~RAB_Parameters_ExtIEs_Extension();
    RAB_Parameters_ExtIEs_Extension & operator = (const RAB_Parameters_ExtIEs_Extension &);
    int operator == (const RAB_Parameters_ExtIEs_Extension &) const;
    int operator != (const RAB_Parameters_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    SignallingIndication *get_SignallingIndication();
    const SignallingIndication *get_SignallingIndication() const;
    void set_SignallingIndication(const SignallingIndication &);
    SignallingIndication *release_SignallingIndication();
    void set_SignallingIndication(SignallingIndication *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq38   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_Parameters_ExtIEs_Extension extensionValue;

    __seq38();
    __seq38(const __seq38 &);
    __seq38(id, criticality, const extensionValue &);

    __seq38 & operator = (const __seq38 &);
    int operator == (const __seq38 &) const;
    int operator != (const __seq38 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

typedef OSS_UINT32 RAB_SubflowCombinationBitRate;

class OSS_PUBLIC RAB_TrCH_MappingItem_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_TrCH_MappingItem_ExtIEs_Extension();
    RAB_TrCH_MappingItem_ExtIEs_Extension(const RAB_TrCH_MappingItem_ExtIEs_Extension &);
    ~RAB_TrCH_MappingItem_ExtIEs_Extension();
    RAB_TrCH_MappingItem_ExtIEs_Extension & operator = (const RAB_TrCH_MappingItem_ExtIEs_Extension &);
    int operator == (const RAB_TrCH_MappingItem_ExtIEs_Extension &) const;
    int operator != (const RAB_TrCH_MappingItem_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC TrCH_ID;

class OSS_PUBLIC __shared6 : public OssList  /* SEQUENCE OF */
{
public:
    typedef TrCH_ID component;

    __shared6();
    __shared6(const __shared6 &);
    ~__shared6();

    __shared6 & operator = (const __shared6 &);
    int operator == (const __shared6 &) const;
    int operator != (const __shared6 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared6 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared6 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared6 *extract_after(OssIndex, OssIndex);
};

typedef __shared6 TrCH_ID_List;

class OSS_PUBLIC __seq39;

class OSS_PUBLIC __seqof33 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq39 component;

    __seqof33();
    __seqof33(const __seqof33 &);
    ~__seqof33();

    __seqof33 & operator = (const __seqof33 &);
    int operator == (const __seqof33 &) const;
    int operator != (const __seqof33 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof33 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof33 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof33 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_TrCH_MappingItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef __shared6 trCH_ID_List;
    typedef __seqof33 iE_Extensions;

    RAB_TrCH_MappingItem();
    RAB_TrCH_MappingItem(const RAB_TrCH_MappingItem &);
    RAB_TrCH_MappingItem(const rAB_ID &, const trCH_ID_List &, const iE_Extensions &);
    RAB_TrCH_MappingItem(const rAB_ID &, const trCH_ID_List &);

    RAB_TrCH_MappingItem & operator = (const RAB_TrCH_MappingItem &);
    int operator == (const RAB_TrCH_MappingItem &) const;
    int operator != (const RAB_TrCH_MappingItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    trCH_ID_List & get_trCH_ID_List();
    const trCH_ID_List & get_trCH_ID_List() const;
    void set_trCH_ID_List(const trCH_ID_List &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    trCH_ID_List trCH_ID_List_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq39   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_TrCH_MappingItem_ExtIEs_Extension extensionValue;

    __seq39();
    __seq39(const __seq39 &);
    __seq39(id, criticality, const extensionValue &);

    __seq39 & operator = (const __seq39 &);
    int operator == (const __seq39 &) const;
    int operator != (const __seq39 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC RAB_TrCH_Mapping : public OssList  /* SEQUENCE OF */
{
public:
    typedef RAB_TrCH_MappingItem component;

    RAB_TrCH_Mapping();
    RAB_TrCH_Mapping(const RAB_TrCH_Mapping &);
    ~RAB_TrCH_Mapping();

    RAB_TrCH_Mapping & operator = (const RAB_TrCH_Mapping &);
    int operator == (const RAB_TrCH_Mapping &) const;
    int operator != (const RAB_TrCH_Mapping &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_TrCH_Mapping *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_TrCH_Mapping *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_TrCH_Mapping *extract_after(OssIndex, OssIndex);
};

typedef __shared9 Requested_RAB_Parameter_MaxBitrateList;

typedef __shared9 Requested_RAB_Parameter_GuaranteedBitrateList;

class OSS_PUBLIC Requested_RAB_Parameter_Values   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared9 requestedMaxBitrates;
    typedef __shared9 requestedGuaranteedBitrates;
    typedef __shared4 iE_Extensions;

    Requested_RAB_Parameter_Values();
    Requested_RAB_Parameter_Values(const Requested_RAB_Parameter_Values &);
    Requested_RAB_Parameter_Values(const requestedMaxBitrates &, const requestedGuaranteedBitrates &, 
	const iE_Extensions &);

    Requested_RAB_Parameter_Values & operator = (const Requested_RAB_Parameter_Values &);
    int operator == (const Requested_RAB_Parameter_Values &) const;
    int operator != (const Requested_RAB_Parameter_Values &) const;

    requestedMaxBitrates *get_requestedMaxBitrates();
    const requestedMaxBitrates *get_requestedMaxBitrates() const;
    void set_requestedMaxBitrates(const requestedMaxBitrates &);
    int requestedMaxBitrates_is_present() const;
    void omit_requestedMaxBitrates();

    requestedGuaranteedBitrates *get_requestedGuaranteedBitrates();
    const requestedGuaranteedBitrates *get_requestedGuaranteedBitrates() const;
    void set_requestedGuaranteedBitrates(const requestedGuaranteedBitrates &);
    int requestedGuaranteedBitrates_is_present() const;
    void omit_requestedGuaranteedBitrates();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    requestedMaxBitrates requestedMaxBitrates_field;
    requestedGuaranteedBitrates requestedGuaranteedBitrates_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RequestType   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef enum Event event;
    typedef enum ReportArea reportArea;
    typedef OSS_UINT32 accuracyCode;

    RequestType();
    RequestType(const RequestType &);
    RequestType(event, reportArea, accuracyCode);
    RequestType(event, reportArea);

    RequestType & operator = (const RequestType &);
    int operator == (const RequestType &) const;
    int operator != (const RequestType &) const;

    event & get_event();
    event get_event() const;
    void set_event(event);

    reportArea & get_reportArea();
    reportArea get_reportArea() const;
    void set_reportArea(reportArea);

    accuracyCode *get_accuracyCode();
    const accuracyCode *get_accuracyCode() const;
    void set_accuracyCode(accuracyCode);
    int accuracyCode_is_present() const;
    void omit_accuracyCode();
private:
    OSS_UINT32 bit_mask;
    event event_field;
    reportArea reportArea_field;
    accuracyCode accuracyCode_field;
};

class OSS_PUBLIC __shared10   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 mantissa;
    typedef OSS_UINT32 exponent;
    typedef __shared4 iE_Extensions;

    __shared10();
    __shared10(const __shared10 &);
    __shared10(mantissa, exponent, const iE_Extensions &);
    __shared10(mantissa, exponent);

    __shared10 & operator = (const __shared10 &);
    int operator == (const __shared10 &) const;
    int operator != (const __shared10 &) const;

    mantissa & get_mantissa();
    mantissa get_mantissa() const;
    void set_mantissa(mantissa);

    exponent & get_exponent();
    exponent get_exponent() const;
    void set_exponent(exponent);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    mantissa mantissa_field;
    exponent exponent_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared10 SDU_ErrorRatio;

typedef __shared10 ResidualBitErrorRatio;

typedef OssString RIMInformation;

typedef OSS_UINT32 SubflowSDU_Size;

class OSS_PUBLIC __seq48;

class OSS_PUBLIC SDU_FormatInformationParameters : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq48 component;

    SDU_FormatInformationParameters();
    SDU_FormatInformationParameters(const SDU_FormatInformationParameters &);
    ~SDU_FormatInformationParameters();

    SDU_FormatInformationParameters & operator = (const SDU_FormatInformationParameters &);
    int operator == (const SDU_FormatInformationParameters &) const;
    int operator != (const SDU_FormatInformationParameters &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(SDU_FormatInformationParameters *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, SDU_FormatInformationParameters *);

    int remove_front();
    int remove_after(OssIndex);

    SDU_FormatInformationParameters *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq48   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 subflowSDU_Size;
    typedef OSS_UINT32 rAB_SubflowCombinationBitRate;
    typedef __shared4 iE_Extensions;

    __seq48();
    __seq48(const __seq48 &);
    __seq48(subflowSDU_Size, rAB_SubflowCombinationBitRate, const iE_Extensions &);

    __seq48 & operator = (const __seq48 &);
    int operator == (const __seq48 &) const;
    int operator != (const __seq48 &) const;

    subflowSDU_Size *get_subflowSDU_Size();
    const subflowSDU_Size *get_subflowSDU_Size() const;
    void set_subflowSDU_Size(subflowSDU_Size);
    int subflowSDU_Size_is_present() const;
    void omit_subflowSDU_Size();

    rAB_SubflowCombinationBitRate *get_rAB_SubflowCombinationBitRate();
    const rAB_SubflowCombinationBitRate *get_rAB_SubflowCombinationBitRate() const;
    void set_rAB_SubflowCombinationBitRate(rAB_SubflowCombinationBitRate);
    int rAB_SubflowCombinationBitRate_is_present() const;
    void omit_rAB_SubflowCombinationBitRate();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    subflowSDU_Size subflowSDU_Size_field;
    rAB_SubflowCombinationBitRate rAB_SubflowCombinationBitRate_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq50   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared10 sDU_ErrorRatio;
    typedef __shared10 residualBitErrorRatio;
    typedef enum DeliveryOfErroneousSDU deliveryOfErroneousSDU;
    typedef SDU_FormatInformationParameters sDU_FormatInformationParameters;
    typedef __shared4 iE_Extensions;

    __seq50();
    __seq50(const __seq50 &);
    __seq50(const sDU_ErrorRatio &, const residualBitErrorRatio &, deliveryOfErroneousSDU, 
	const sDU_FormatInformationParameters &, const iE_Extensions &);
    __seq50(const residualBitErrorRatio &, deliveryOfErroneousSDU);

    __seq50 & operator = (const __seq50 &);
    int operator == (const __seq50 &) const;
    int operator != (const __seq50 &) const;

    sDU_ErrorRatio *get_sDU_ErrorRatio();
    const sDU_ErrorRatio *get_sDU_ErrorRatio() const;
    void set_sDU_ErrorRatio(const sDU_ErrorRatio &);
    int sDU_ErrorRatio_is_present() const;
    void omit_sDU_ErrorRatio();

    residualBitErrorRatio & get_residualBitErrorRatio();
    const residualBitErrorRatio & get_residualBitErrorRatio() const;
    void set_residualBitErrorRatio(const residualBitErrorRatio &);

    deliveryOfErroneousSDU & get_deliveryOfErroneousSDU();
    deliveryOfErroneousSDU get_deliveryOfErroneousSDU() const;
    void set_deliveryOfErroneousSDU(deliveryOfErroneousSDU);

    sDU_FormatInformationParameters *get_sDU_FormatInformationParameters();
    const sDU_FormatInformationParameters *get_sDU_FormatInformationParameters() const;
    void set_sDU_FormatInformationParameters(const sDU_FormatInformationParameters &);
    int sDU_FormatInformationParameters_is_present() const;
    void omit_sDU_FormatInformationParameters();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    sDU_ErrorRatio sDU_ErrorRatio_field;
    residualBitErrorRatio residualBitErrorRatio_field;
    deliveryOfErroneousSDU deliveryOfErroneousSDU_field;
    sDU_FormatInformationParameters sDU_FormatInformationParameters_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SNA_Access_Information   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef AuthorisedPLMNs authorisedPLMNs;
    typedef __shared4 iE_Extensions;

    SNA_Access_Information();
    SNA_Access_Information(const SNA_Access_Information &);
    SNA_Access_Information(const authorisedPLMNs &, const iE_Extensions &);
    SNA_Access_Information(const authorisedPLMNs &);

    SNA_Access_Information & operator = (const SNA_Access_Information &);
    int operator == (const SNA_Access_Information &) const;
    int operator != (const SNA_Access_Information &) const;

    authorisedPLMNs & get_authorisedPLMNs();
    const authorisedPLMNs & get_authorisedPLMNs() const;
    void set_authorisedPLMNs(const authorisedPLMNs &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    authorisedPLMNs authorisedPLMNs_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SourceRNC_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString pLMNidentity;
    typedef OSS_UINT32 rNC_ID;
    typedef __shared4 iE_Extensions;

    SourceRNC_ID();
    SourceRNC_ID(const SourceRNC_ID &);
    SourceRNC_ID(const pLMNidentity &, rNC_ID, const iE_Extensions &);
    SourceRNC_ID(const pLMNidentity &, rNC_ID);

    SourceRNC_ID & operator = (const SourceRNC_ID &);
    int operator == (const SourceRNC_ID &) const;
    int operator != (const SourceRNC_ID &) const;

    pLMNidentity & get_pLMNidentity();
    const pLMNidentity & get_pLMNidentity() const;
    void set_pLMNidentity(const pLMNidentity &);

    rNC_ID & get_rNC_ID();
    rNC_ID get_rNC_ID() const;
    void set_rNC_ID(rNC_ID);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    pLMNidentity pLMNidentity_field;
    rNC_ID rNC_ID_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SourceID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	sourceRNC_ID_chosen = 1,
	sAI_chosen = 2
    };
    typedef SourceRNC_ID sourceRNC_ID;
    typedef SAI sAI;

    SourceID();
    SourceID(const SourceID &);
    ~SourceID();

    SourceID & operator = (const SourceID &);
    int operator == (const SourceID &) const;
    int operator != (const SourceID &) const;

    sourceRNC_ID *get_sourceRNC_ID();
    const sourceRNC_ID *get_sourceRNC_ID() const;
    void set_sourceRNC_ID(const sourceRNC_ID &);

    sAI *get_sAI();
    const sAI *get_sAI() const;
    void set_sAI(const sAI &);
private:
    union {
	sourceRNC_ID *sourceRNC_ID_field;
	sAI *sAI_field;
    };
    void cleanup();
};

typedef OSS_UINT32 TargetCellId;

class OSS_PUBLIC SRB_TrCH_MappingItem;

class OSS_PUBLIC SRB_TrCH_Mapping : public OssList  /* SEQUENCE OF */
{
public:
    typedef SRB_TrCH_MappingItem component;

    SRB_TrCH_Mapping();
    SRB_TrCH_Mapping(const SRB_TrCH_Mapping &);
    ~SRB_TrCH_Mapping();

    SRB_TrCH_Mapping & operator = (const SRB_TrCH_Mapping &);
    int operator == (const SRB_TrCH_Mapping &) const;
    int operator != (const SRB_TrCH_Mapping &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(SRB_TrCH_Mapping *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, SRB_TrCH_Mapping *);

    int remove_front();
    int remove_after(OssIndex);

    SRB_TrCH_Mapping *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC TraceRecordingSessionInformation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString traceReference;
    typedef OSS_UINT32 traceRecordingSessionReference;
    typedef __shared4 iE_Extensions;

    TraceRecordingSessionInformation();
    TraceRecordingSessionInformation(const TraceRecordingSessionInformation &);
    TraceRecordingSessionInformation(const traceReference &, traceRecordingSessionReference, 
	const iE_Extensions &);
    TraceRecordingSessionInformation(const traceReference &, traceRecordingSessionReference);

    TraceRecordingSessionInformation & operator = (const TraceRecordingSessionInformation &);
    int operator == (const TraceRecordingSessionInformation &) const;
    int operator != (const TraceRecordingSessionInformation &) const;

    traceReference & get_traceReference();
    const traceReference & get_traceReference() const;
    void set_traceReference(const traceReference &);

    traceRecordingSessionReference & get_traceRecordingSessionReference();
    traceRecordingSessionReference get_traceRecordingSessionReference() const;
    void set_traceRecordingSessionReference(traceRecordingSessionReference);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    traceReference traceReference_field;
    traceRecordingSessionReference traceRecordingSessionReference_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension();
    SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension(const SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension &);
    ~SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension();
    SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension & operator = (const SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension &);
    int operator == (const SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension &) const;
    int operator != (const SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    SRB_TrCH_Mapping *get_SRB_TrCH_Mapping();
    const SRB_TrCH_Mapping *get_SRB_TrCH_Mapping() const;
    void set_SRB_TrCH_Mapping(const SRB_TrCH_Mapping &);
    SRB_TrCH_Mapping *release_SRB_TrCH_Mapping();
    void set_SRB_TrCH_Mapping(SRB_TrCH_Mapping *);

    CellLoadInformationGroup *get_CellLoadInformationGroup();
    const CellLoadInformationGroup *get_CellLoadInformationGroup() const;
    void set_CellLoadInformationGroup(const CellLoadInformationGroup &);
    CellLoadInformationGroup *release_CellLoadInformationGroup();
    void set_CellLoadInformationGroup(CellLoadInformationGroup *);

    TraceRecordingSessionInformation *get_TraceRecordingSessionInformation();
    const TraceRecordingSessionInformation *get_TraceRecordingSessionInformation() const;
    void set_TraceRecordingSessionInformation(const TraceRecordingSessionInformation &);
    TraceRecordingSessionInformation *release_TraceRecordingSessionInformation();
    void set_TraceRecordingSessionInformation(TraceRecordingSessionInformation *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq53;

class OSS_PUBLIC __seqof45 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq53 component;

    __seqof45();
    __seqof45(const __seqof45 &);
    ~__seqof45();

    __seqof45 & operator = (const __seqof45 &);
    int operator == (const __seqof45 &) const;
    int operator != (const __seqof45 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof45 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof45 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof45 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SourceRNC_ToTargetRNC_TransparentContainer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString rRC_Container;
    typedef OSS_UINT32 numberOfIuInstances;
    typedef enum RelocationType relocationType;
    typedef OSS_UINT32 chosenIntegrityProtectionAlgorithm;
    typedef OssBitString integrityProtectionKey;
    typedef OSS_UINT32 chosenEncryptionAlgorithForSignalling;
    typedef OssBitString cipheringKey;
    typedef OSS_UINT32 chosenEncryptionAlgorithForCS;
    typedef OSS_UINT32 chosenEncryptionAlgorithForPS;
    typedef OSS_UINT32 d_RNTI;
    typedef OSS_UINT32 targetCellId;
    typedef RAB_TrCH_Mapping rAB_TrCH_Mapping;
    typedef __seqof45 iE_Extensions;

    SourceRNC_ToTargetRNC_TransparentContainer();
    SourceRNC_ToTargetRNC_TransparentContainer(const SourceRNC_ToTargetRNC_TransparentContainer &);
    SourceRNC_ToTargetRNC_TransparentContainer(const rRC_Container &, numberOfIuInstances, 
	relocationType, chosenIntegrityProtectionAlgorithm, const integrityProtectionKey &, 
	chosenEncryptionAlgorithForSignalling, const cipheringKey &, chosenEncryptionAlgorithForCS, 
	chosenEncryptionAlgorithForPS, d_RNTI, targetCellId, const rAB_TrCH_Mapping &, const iE_Extensions &);
    SourceRNC_ToTargetRNC_TransparentContainer(const rRC_Container &, numberOfIuInstances, 
	relocationType);

    SourceRNC_ToTargetRNC_TransparentContainer & operator = (const SourceRNC_ToTargetRNC_TransparentContainer &);
    int operator == (const SourceRNC_ToTargetRNC_TransparentContainer &) const;
    int operator != (const SourceRNC_ToTargetRNC_TransparentContainer &) const;

    rRC_Container & get_rRC_Container();
    const rRC_Container & get_rRC_Container() const;
    void set_rRC_Container(const rRC_Container &);

    numberOfIuInstances & get_numberOfIuInstances();
    numberOfIuInstances get_numberOfIuInstances() const;
    void set_numberOfIuInstances(numberOfIuInstances);

    relocationType & get_relocationType();
    relocationType get_relocationType() const;
    void set_relocationType(relocationType);

    chosenIntegrityProtectionAlgorithm *get_chosenIntegrityProtectionAlgorithm();
    const chosenIntegrityProtectionAlgorithm *get_chosenIntegrityProtectionAlgorithm() const;
    void set_chosenIntegrityProtectionAlgorithm(chosenIntegrityProtectionAlgorithm);
    int chosenIntegrityProtectionAlgorithm_is_present() const;
    void omit_chosenIntegrityProtectionAlgorithm();

    integrityProtectionKey *get_integrityProtectionKey();
    const integrityProtectionKey *get_integrityProtectionKey() const;
    void set_integrityProtectionKey(const integrityProtectionKey &);
    int integrityProtectionKey_is_present() const;
    void omit_integrityProtectionKey();

    chosenEncryptionAlgorithForSignalling *get_chosenEncryptionAlgorithForSignalling();
    const chosenEncryptionAlgorithForSignalling *get_chosenEncryptionAlgorithForSignalling() const;
    void set_chosenEncryptionAlgorithForSignalling(chosenEncryptionAlgorithForSignalling);
    int chosenEncryptionAlgorithForSignalling_is_present() const;
    void omit_chosenEncryptionAlgorithForSignalling();

    cipheringKey *get_cipheringKey();
    const cipheringKey *get_cipheringKey() const;
    void set_cipheringKey(const cipheringKey &);
    int cipheringKey_is_present() const;
    void omit_cipheringKey();

    chosenEncryptionAlgorithForCS *get_chosenEncryptionAlgorithForCS();
    const chosenEncryptionAlgorithForCS *get_chosenEncryptionAlgorithForCS() const;
    void set_chosenEncryptionAlgorithForCS(chosenEncryptionAlgorithForCS);
    int chosenEncryptionAlgorithForCS_is_present() const;
    void omit_chosenEncryptionAlgorithForCS();

    chosenEncryptionAlgorithForPS *get_chosenEncryptionAlgorithForPS();
    const chosenEncryptionAlgorithForPS *get_chosenEncryptionAlgorithForPS() const;
    void set_chosenEncryptionAlgorithForPS(chosenEncryptionAlgorithForPS);
    int chosenEncryptionAlgorithForPS_is_present() const;
    void omit_chosenEncryptionAlgorithForPS();

    d_RNTI *get_d_RNTI();
    const d_RNTI *get_d_RNTI() const;
    void set_d_RNTI(d_RNTI);
    int d_RNTI_is_present() const;
    void omit_d_RNTI();

    targetCellId *get_targetCellId();
    const targetCellId *get_targetCellId() const;
    void set_targetCellId(targetCellId);
    int targetCellId_is_present() const;
    void omit_targetCellId();

    rAB_TrCH_Mapping *get_rAB_TrCH_Mapping();
    const rAB_TrCH_Mapping *get_rAB_TrCH_Mapping() const;
    void set_rAB_TrCH_Mapping(const rAB_TrCH_Mapping &);
    int rAB_TrCH_Mapping_is_present() const;
    void omit_rAB_TrCH_Mapping();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rRC_Container rRC_Container_field;
    numberOfIuInstances numberOfIuInstances_field;
    relocationType relocationType_field;
    chosenIntegrityProtectionAlgorithm chosenIntegrityProtectionAlgorithm_field;
    integrityProtectionKey integrityProtectionKey_field;
    chosenEncryptionAlgorithForSignalling chosenEncryptionAlgorithForSignalling_field;
    cipheringKey cipheringKey_field;
    chosenEncryptionAlgorithForCS chosenEncryptionAlgorithForCS_field;
    chosenEncryptionAlgorithForPS chosenEncryptionAlgorithForPS_field;
    d_RNTI d_RNTI_field;
    targetCellId targetCellId_field;
    rAB_TrCH_Mapping rAB_TrCH_Mapping_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq53   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SourceRNC_ToTargetRNC_TransparentContainer_ExtIEs_Extension extensionValue;

    __seq53();
    __seq53(const __seq53 &);
    __seq53(id, criticality, const extensionValue &);

    __seq53 & operator = (const __seq53 &);
    int operator == (const __seq53 &) const;
    int operator != (const __seq53 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

typedef OSS_UINT32 SRB_ID;

typedef OSS_UINT32 USCH_ID;

class OSS_PUBLIC TrCH_ID_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    TrCH_ID_ExtIEs_Extension();
    TrCH_ID_ExtIEs_Extension(const TrCH_ID_ExtIEs_Extension &);
    ~TrCH_ID_ExtIEs_Extension();
    TrCH_ID_ExtIEs_Extension & operator = (const TrCH_ID_ExtIEs_Extension &);
    int operator == (const TrCH_ID_ExtIEs_Extension &) const;
    int operator != (const TrCH_ID_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    HS_DSCH_MAC_d_Flow_ID *get_HS_DSCH_MAC_d_Flow_ID();
    const HS_DSCH_MAC_d_Flow_ID *get_HS_DSCH_MAC_d_Flow_ID() const;
    void set_HS_DSCH_MAC_d_Flow_ID(const HS_DSCH_MAC_d_Flow_ID &);
    HS_DSCH_MAC_d_Flow_ID *release_HS_DSCH_MAC_d_Flow_ID();
    void set_HS_DSCH_MAC_d_Flow_ID(HS_DSCH_MAC_d_Flow_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq55;

class OSS_PUBLIC __seqof47 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq55 component;

    __seqof47();
    __seqof47(const __seqof47 &);
    ~__seqof47();

    __seqof47 & operator = (const __seqof47 &);
    int operator == (const __seqof47 &) const;
    int operator != (const __seqof47 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof47 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof47 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof47 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC TrCH_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 dCH_ID;
    typedef OSS_UINT32 dSCH_ID;
    typedef OSS_UINT32 uSCH_ID;
    typedef __seqof47 iE_Extensions;

    TrCH_ID();
    TrCH_ID(const TrCH_ID &);
    TrCH_ID(dCH_ID, dSCH_ID, uSCH_ID, const iE_Extensions &);

    TrCH_ID & operator = (const TrCH_ID &);
    int operator == (const TrCH_ID &) const;
    int operator != (const TrCH_ID &) const;

    dCH_ID *get_dCH_ID();
    const dCH_ID *get_dCH_ID() const;
    void set_dCH_ID(dCH_ID);
    int dCH_ID_is_present() const;
    void omit_dCH_ID();

    dSCH_ID *get_dSCH_ID();
    const dSCH_ID *get_dSCH_ID() const;
    void set_dSCH_ID(dSCH_ID);
    int dSCH_ID_is_present() const;
    void omit_dSCH_ID();

    uSCH_ID *get_uSCH_ID();
    const uSCH_ID *get_uSCH_ID() const;
    void set_uSCH_ID(uSCH_ID);
    int uSCH_ID_is_present() const;
    void omit_uSCH_ID();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    dCH_ID dCH_ID_field;
    dSCH_ID dSCH_ID_field;
    uSCH_ID uSCH_ID_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC __seq55   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef TrCH_ID_ExtIEs_Extension extensionValue;

    __seq55();
    __seq55(const __seq55 &);
    __seq55(id, criticality, const extensionValue &);

    __seq55 & operator = (const __seq55 &);
    int operator == (const __seq55 &) const;
    int operator != (const __seq55 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC SRB_TrCH_MappingItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 sRB_ID;
    typedef TrCH_ID trCH_ID;
    typedef __shared4 iE_Extensions;

    SRB_TrCH_MappingItem();
    SRB_TrCH_MappingItem(const SRB_TrCH_MappingItem &);
    SRB_TrCH_MappingItem(sRB_ID, const trCH_ID &, const iE_Extensions &);
    SRB_TrCH_MappingItem(sRB_ID, const trCH_ID &);

    SRB_TrCH_MappingItem & operator = (const SRB_TrCH_MappingItem &);
    int operator == (const SRB_TrCH_MappingItem &) const;
    int operator != (const SRB_TrCH_MappingItem &) const;

    sRB_ID & get_sRB_ID();
    sRB_ID get_sRB_ID() const;
    void set_sRB_ID(sRB_ID);

    trCH_ID & get_trCH_ID();
    const trCH_ID & get_trCH_ID() const;
    void set_trCH_ID(const trCH_ID &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    sRB_ID sRB_ID_field;
    trCH_ID trCH_ID_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC TargetRNC_ID   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef LAI lAI;
    typedef OssString rAC;
    typedef OSS_UINT32 rNC_ID;
    typedef __shared4 iE_Extensions;

    TargetRNC_ID();
    TargetRNC_ID(const TargetRNC_ID &);
    TargetRNC_ID(const lAI &, const rAC &, rNC_ID, const iE_Extensions &);
    TargetRNC_ID(const lAI &, rNC_ID);

    TargetRNC_ID & operator = (const TargetRNC_ID &);
    int operator == (const TargetRNC_ID &) const;
    int operator != (const TargetRNC_ID &) const;

    lAI & get_lAI();
    const lAI & get_lAI() const;
    void set_lAI(const lAI &);

    rAC *get_rAC();
    const rAC *get_rAC() const;
    void set_rAC(const rAC &);
    int rAC_is_present() const;
    void omit_rAC();

    rNC_ID & get_rNC_ID();
    rNC_ID get_rNC_ID() const;
    void set_rNC_ID(rNC_ID);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    lAI lAI_field;
    rAC rAC_field;
    rNC_ID rNC_ID_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC TargetID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	targetRNC_ID_chosen = 1,
	cGI_chosen = 2
    };
    typedef TargetRNC_ID targetRNC_ID;
    typedef CGI cGI;

    TargetID();
    TargetID(const TargetID &);
    ~TargetID();

    TargetID & operator = (const TargetID &);
    int operator == (const TargetID &) const;
    int operator != (const TargetID &) const;

    targetRNC_ID *get_targetRNC_ID();
    const targetRNC_ID *get_targetRNC_ID() const;
    void set_targetRNC_ID(const targetRNC_ID &);

    cGI *get_cGI();
    const cGI *get_cGI() const;
    void set_cGI(const cGI &);
private:
    union {
	targetRNC_ID *targetRNC_ID_field;
	cGI *cGI_field;
    };
    void cleanup();
};

class OSS_PUBLIC TargetRNC_ToSourceRNC_TransparentContainer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString rRC_Container;
    typedef OSS_UINT32 d_RNTI;
    typedef __shared4 iE_Extensions;

    TargetRNC_ToSourceRNC_TransparentContainer();
    TargetRNC_ToSourceRNC_TransparentContainer(const TargetRNC_ToSourceRNC_TransparentContainer &);
    TargetRNC_ToSourceRNC_TransparentContainer(const rRC_Container &, d_RNTI, const iE_Extensions &);
    TargetRNC_ToSourceRNC_TransparentContainer(const rRC_Container &);

    TargetRNC_ToSourceRNC_TransparentContainer & operator = (const TargetRNC_ToSourceRNC_TransparentContainer &);
    int operator == (const TargetRNC_ToSourceRNC_TransparentContainer &) const;
    int operator != (const TargetRNC_ToSourceRNC_TransparentContainer &) const;

    rRC_Container & get_rRC_Container();
    const rRC_Container & get_rRC_Container() const;
    void set_rRC_Container(const rRC_Container &);

    d_RNTI *get_d_RNTI();
    const d_RNTI *get_d_RNTI() const;
    void set_d_RNTI(d_RNTI);
    int d_RNTI_is_present() const;
    void omit_d_RNTI();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rRC_Container rRC_Container_field;
    d_RNTI d_RNTI_field;
    iE_Extensions iE_Extensions_field;
};

typedef OssString TMSI;

class OSS_PUBLIC TemporaryUE_ID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	tMSI_chosen = 1,
	p_TMSI_chosen = 2
    };
    typedef OssString tMSI;
    typedef OssString p_TMSI;

    TemporaryUE_ID();
    TemporaryUE_ID(const TemporaryUE_ID &);
    ~TemporaryUE_ID();

    TemporaryUE_ID & operator = (const TemporaryUE_ID &);
    int operator == (const TemporaryUE_ID &) const;
    int operator != (const TemporaryUE_ID &) const;

    tMSI *get_tMSI();
    const tMSI *get_tMSI() const;
    void set_tMSI(const tMSI &);

    p_TMSI *get_p_TMSI();
    const p_TMSI *get_p_TMSI() const;
    void set_p_TMSI(const p_TMSI &);
private:
    union {
	OSSC::COssString tMSI_field;
	OSSC::COssString p_TMSI_field;
    };
    void cleanup();
};

typedef OSS_UINT32 TraceRecordingSessionReference;

class OSS_PUBLIC TracePropagationParameters   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 traceRecordingSessionReference;
    typedef enum TraceDepth traceDepth;
    typedef ListOfInterfacesToTrace listOfInterfacesToTrace;
    typedef __shared4 iE_Extensions;

    TracePropagationParameters();
    TracePropagationParameters(const TracePropagationParameters &);
    TracePropagationParameters(traceRecordingSessionReference, traceDepth, const listOfInterfacesToTrace &, 
	const iE_Extensions &);
    TracePropagationParameters(traceRecordingSessionReference, traceDepth);

    TracePropagationParameters & operator = (const TracePropagationParameters &);
    int operator == (const TracePropagationParameters &) const;
    int operator != (const TracePropagationParameters &) const;

    traceRecordingSessionReference & get_traceRecordingSessionReference();
    traceRecordingSessionReference get_traceRecordingSessionReference() const;
    void set_traceRecordingSessionReference(traceRecordingSessionReference);

    traceDepth & get_traceDepth();
    traceDepth get_traceDepth() const;
    void set_traceDepth(traceDepth);

    listOfInterfacesToTrace *get_listOfInterfacesToTrace();
    const listOfInterfacesToTrace *get_listOfInterfacesToTrace() const;
    void set_listOfInterfacesToTrace(const listOfInterfacesToTrace &);
    int listOfInterfacesToTrace_is_present() const;
    void omit_listOfInterfacesToTrace();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    traceRecordingSessionReference traceRecordingSessionReference_field;
    traceDepth traceDepth_field;
    listOfInterfacesToTrace listOfInterfacesToTrace_field;
    iE_Extensions iE_Extensions_field;
};

typedef OSS_UINT32 UnsuccessfullyTransmittedDataVolume;

class OSS_PUBLIC UE_ID  : public OssChoice   /* CHOICE */
{
public:
    enum Id {
	unselected,
	imsi_chosen = 1,
	imei_chosen = 2,
	imeisv_chosen = 3
    };
    typedef OssString imsi;
    typedef OssString imei;
    typedef OssString imeisv;

    UE_ID();
    UE_ID(const UE_ID &);
    ~UE_ID();

    UE_ID & operator = (const UE_ID &);
    int operator == (const UE_ID &) const;
    int operator != (const UE_ID &) const;

    imsi *get_imsi();
    const imsi *get_imsi() const;
    void set_imsi(const imsi &);

    imei *get_imei();
    const imei *get_imei() const;
    void set_imei(const imei &);

    imeisv *get_imeisv();
    const imeisv *get_imeisv() const;
    void set_imeisv(const imeisv &);
private:
    union {
	OSSC::COssString imsi_field;
	OSSC::COssString imei_field;
	OSSC::COssString imeisv_field;
    };
    void cleanup();
};

typedef OssBitString UESBI_IuA;

typedef OssBitString UESBI_IuB;

class OSS_PUBLIC UESBI_Iu   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString uESBI_IuA;
    typedef OssBitString uESBI_IuB;
    typedef __shared4 iE_Extensions;

    UESBI_Iu();
    UESBI_Iu(const UESBI_Iu &);
    UESBI_Iu(const uESBI_IuA &, const uESBI_IuB &, const iE_Extensions &);

    UESBI_Iu & operator = (const UESBI_Iu &);
    int operator == (const UESBI_Iu &) const;
    int operator != (const UESBI_Iu &) const;

    uESBI_IuA *get_uESBI_IuA();
    const uESBI_IuA *get_uESBI_IuA() const;
    void set_uESBI_IuA(const uESBI_IuA &);
    int uESBI_IuA_is_present() const;
    void omit_uESBI_IuA();

    uESBI_IuB *get_uESBI_IuB();
    const uESBI_IuB *get_uESBI_IuB() const;
    void set_uESBI_IuB(const uESBI_IuB &);
    int uESBI_IuB_is_present() const;
    void omit_uESBI_IuB();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    uESBI_IuA uESBI_IuA_field;
    uESBI_IuB uESBI_IuB_field;
    iE_Extensions iE_Extensions_field;
};

typedef OSS_UINT32 UL_GTP_PDU_SequenceNumber;

typedef OSS_UINT32 UL_N_PDU_SequenceNumber;

typedef OssBitString UP_ModeVersions;

class OSS_PUBLIC Iu_ReleaseCommandIEs_Value : public OssConstrainedOpenType
{
public:
    Iu_ReleaseCommandIEs_Value();
    Iu_ReleaseCommandIEs_Value(const Iu_ReleaseCommandIEs_Value &);
    ~Iu_ReleaseCommandIEs_Value();
    Iu_ReleaseCommandIEs_Value & operator = (const Iu_ReleaseCommandIEs_Value &);
    int operator == (const Iu_ReleaseCommandIEs_Value &) const;
    int operator != (const Iu_ReleaseCommandIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __shared1   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef Iu_ReleaseCommandIEs_Value value;

    __shared1();
    __shared1(const __shared1 &);
    __shared1(id, criticality, const value &);

    __shared1 & operator = (const __shared1 &);
    int operator == (const __shared1 &) const;
    int operator != (const __shared1 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof58;

class OSS_PUBLIC RAB_DataVolumeReportList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof58 component;

    RAB_DataVolumeReportList();
    RAB_DataVolumeReportList(const RAB_DataVolumeReportList &);
    ~RAB_DataVolumeReportList();

    RAB_DataVolumeReportList & operator = (const RAB_DataVolumeReportList &);
    int operator == (const RAB_DataVolumeReportList &) const;
    int operator != (const RAB_DataVolumeReportList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_DataVolumeReportList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_DataVolumeReportList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_DataVolumeReportList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof60;

class OSS_PUBLIC RAB_ReleasedList_IuRelComp : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof60 component;

    RAB_ReleasedList_IuRelComp();
    RAB_ReleasedList_IuRelComp(const RAB_ReleasedList_IuRelComp &);
    ~RAB_ReleasedList_IuRelComp();

    RAB_ReleasedList_IuRelComp & operator = (const RAB_ReleasedList_IuRelComp &);
    int operator == (const RAB_ReleasedList_IuRelComp &) const;
    int operator != (const RAB_ReleasedList_IuRelComp &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ReleasedList_IuRelComp *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ReleasedList_IuRelComp *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ReleasedList_IuRelComp *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC Iu_ReleaseCompleteIEs_Value : public OssConstrainedOpenType
{
public:
    Iu_ReleaseCompleteIEs_Value();
    Iu_ReleaseCompleteIEs_Value(const Iu_ReleaseCompleteIEs_Value &);
    ~Iu_ReleaseCompleteIEs_Value();
    Iu_ReleaseCompleteIEs_Value & operator = (const Iu_ReleaseCompleteIEs_Value &);
    int operator == (const Iu_ReleaseCompleteIEs_Value &) const;
    int operator != (const Iu_ReleaseCompleteIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataVolumeReportList *get_RAB_DataVolumeReportList();
    const RAB_DataVolumeReportList *get_RAB_DataVolumeReportList() const;
    void set_RAB_DataVolumeReportList(const RAB_DataVolumeReportList &);
    RAB_DataVolumeReportList *release_RAB_DataVolumeReportList();
    void set_RAB_DataVolumeReportList(RAB_DataVolumeReportList *);

    RAB_ReleasedList_IuRelComp *get_RAB_ReleasedList_IuRelComp();
    const RAB_ReleasedList_IuRelComp *get_RAB_ReleasedList_IuRelComp() const;
    void set_RAB_ReleasedList_IuRelComp(const RAB_ReleasedList_IuRelComp &);
    RAB_ReleasedList_IuRelComp *release_RAB_ReleasedList_IuRelComp();
    void set_RAB_ReleasedList_IuRelComp(RAB_ReleasedList_IuRelComp *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq64   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef Iu_ReleaseCompleteIEs_Value value;

    __seq64();
    __seq64(const __seq64 &);
    __seq64(id, criticality, const value &);

    __seq64 & operator = (const __seq64 &);
    int operator == (const __seq64 &) const;
    int operator != (const __seq64 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq179;

class OSS_PUBLIC __shared31 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq179 component;

    __shared31();
    __shared31(const __shared31 &);
    ~__shared31();

    __shared31 & operator = (const __shared31 &);
    int operator == (const __shared31 &) const;
    int operator != (const __shared31 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared31 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared31 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared31 *extract_after(OssIndex, OssIndex);
};

typedef __shared31 DataVolumeList;

class OSS_PUBLIC RAB_DataVolumeReportItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef __shared31 dl_UnsuccessfullyTransmittedDataVolume;
    typedef __shared4 iE_Extensions;

    RAB_DataVolumeReportItem();
    RAB_DataVolumeReportItem(const RAB_DataVolumeReportItem &);
    RAB_DataVolumeReportItem(const rAB_ID &, const dl_UnsuccessfullyTransmittedDataVolume &, 
	const iE_Extensions &);
    RAB_DataVolumeReportItem(const rAB_ID &);

    RAB_DataVolumeReportItem & operator = (const RAB_DataVolumeReportItem &);
    int operator == (const RAB_DataVolumeReportItem &) const;
    int operator != (const RAB_DataVolumeReportItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    dl_UnsuccessfullyTransmittedDataVolume *get_dl_UnsuccessfullyTransmittedDataVolume();
    const dl_UnsuccessfullyTransmittedDataVolume *get_dl_UnsuccessfullyTransmittedDataVolume() const;
    void set_dl_UnsuccessfullyTransmittedDataVolume(const dl_UnsuccessfullyTransmittedDataVolume &);
    int dl_UnsuccessfullyTransmittedDataVolume_is_present() const;
    void omit_dl_UnsuccessfullyTransmittedDataVolume();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    dl_UnsuccessfullyTransmittedDataVolume dl_UnsuccessfullyTransmittedDataVolume_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_DataVolumeReportItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_DataVolumeReportItemIEs_Value();
    RAB_DataVolumeReportItemIEs_Value(const RAB_DataVolumeReportItemIEs_Value &);
    ~RAB_DataVolumeReportItemIEs_Value();
    RAB_DataVolumeReportItemIEs_Value & operator = (const RAB_DataVolumeReportItemIEs_Value &);
    int operator == (const RAB_DataVolumeReportItemIEs_Value &) const;
    int operator != (const RAB_DataVolumeReportItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataVolumeReportItem *get_RAB_DataVolumeReportItem();
    const RAB_DataVolumeReportItem *get_RAB_DataVolumeReportItem() const;
    void set_RAB_DataVolumeReportItem(const RAB_DataVolumeReportItem &);
    RAB_DataVolumeReportItem *release_RAB_DataVolumeReportItem();
    void set_RAB_DataVolumeReportItem(RAB_DataVolumeReportItem *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq66;

class OSS_PUBLIC __seqof58 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq66 component;

    __seqof58();
    __seqof58(const __seqof58 &);
    ~__seqof58();

    __seqof58 & operator = (const __seqof58 &);
    int operator == (const __seqof58 &) const;
    int operator != (const __seqof58 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof58 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof58 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof58 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq66   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_DataVolumeReportItemIEs_Value value;

    __seq66();
    __seq66(const __seq66 &);
    __seq66(id, criticality, const value &);

    __seq66 & operator = (const __seq66 &);
    int operator == (const __seq66 &) const;
    int operator != (const __seq66 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_ReleasedItem_IuRelComp   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OSS_UINT32 dL_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 uL_GTP_PDU_SequenceNumber;
    typedef __shared4 iE_Extensions;

    RAB_ReleasedItem_IuRelComp();
    RAB_ReleasedItem_IuRelComp(const RAB_ReleasedItem_IuRelComp &);
    RAB_ReleasedItem_IuRelComp(const rAB_ID &, dL_GTP_PDU_SequenceNumber, uL_GTP_PDU_SequenceNumber, 
	const iE_Extensions &);
    RAB_ReleasedItem_IuRelComp(const rAB_ID &);

    RAB_ReleasedItem_IuRelComp & operator = (const RAB_ReleasedItem_IuRelComp &);
    int operator == (const RAB_ReleasedItem_IuRelComp &) const;
    int operator != (const RAB_ReleasedItem_IuRelComp &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    dL_GTP_PDU_SequenceNumber *get_dL_GTP_PDU_SequenceNumber();
    const dL_GTP_PDU_SequenceNumber *get_dL_GTP_PDU_SequenceNumber() const;
    void set_dL_GTP_PDU_SequenceNumber(dL_GTP_PDU_SequenceNumber);
    int dL_GTP_PDU_SequenceNumber_is_present() const;
    void omit_dL_GTP_PDU_SequenceNumber();

    uL_GTP_PDU_SequenceNumber *get_uL_GTP_PDU_SequenceNumber();
    const uL_GTP_PDU_SequenceNumber *get_uL_GTP_PDU_SequenceNumber() const;
    void set_uL_GTP_PDU_SequenceNumber(uL_GTP_PDU_SequenceNumber);
    int uL_GTP_PDU_SequenceNumber_is_present() const;
    void omit_uL_GTP_PDU_SequenceNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    dL_GTP_PDU_SequenceNumber dL_GTP_PDU_SequenceNumber_field;
    uL_GTP_PDU_SequenceNumber uL_GTP_PDU_SequenceNumber_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_ReleasedItem_IuRelComp_IEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ReleasedItem_IuRelComp_IEs_Value();
    RAB_ReleasedItem_IuRelComp_IEs_Value(const RAB_ReleasedItem_IuRelComp_IEs_Value &);
    ~RAB_ReleasedItem_IuRelComp_IEs_Value();
    RAB_ReleasedItem_IuRelComp_IEs_Value & operator = (const RAB_ReleasedItem_IuRelComp_IEs_Value &);
    int operator == (const RAB_ReleasedItem_IuRelComp_IEs_Value &) const;
    int operator != (const RAB_ReleasedItem_IuRelComp_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ReleasedItem_IuRelComp *get_RAB_ReleasedItem_IuRelComp();
    const RAB_ReleasedItem_IuRelComp *get_RAB_ReleasedItem_IuRelComp() const;
    void set_RAB_ReleasedItem_IuRelComp(const RAB_ReleasedItem_IuRelComp &);
    RAB_ReleasedItem_IuRelComp *release_RAB_ReleasedItem_IuRelComp();
    void set_RAB_ReleasedItem_IuRelComp(RAB_ReleasedItem_IuRelComp *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq68;

class OSS_PUBLIC __seqof60 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq68 component;

    __seqof60();
    __seqof60(const __seqof60 &);
    ~__seqof60();

    __seqof60 & operator = (const __seqof60 &);
    int operator == (const __seqof60 &) const;
    int operator != (const __seqof60 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof60 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof60 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof60 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq68   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ReleasedItem_IuRelComp_IEs_Value value;

    __seq68();
    __seq68(const __seq68 &);
    __seq68(id, criticality, const value &);

    __seq68 & operator = (const __seq68 &);
    int operator == (const __seq68 &) const;
    int operator != (const __seq68 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RelocationRequiredIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationRequiredIEs_Value();
    RelocationRequiredIEs_Value(const RelocationRequiredIEs_Value &);
    ~RelocationRequiredIEs_Value();
    RelocationRequiredIEs_Value & operator = (const RelocationRequiredIEs_Value &);
    int operator == (const RelocationRequiredIEs_Value &) const;
    int operator != (const RelocationRequiredIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RelocationType *get_RelocationType();
    const RelocationType *get_RelocationType() const;
    void set_RelocationType(const RelocationType &);
    RelocationType *release_RelocationType();
    void set_RelocationType(RelocationType *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    SourceID *get_SourceID();
    const SourceID *get_SourceID() const;
    void set_SourceID(const SourceID &);
    SourceID *release_SourceID();
    void set_SourceID(SourceID *);

    TargetID *get_TargetID();
    const TargetID *get_TargetID() const;
    void set_TargetID(const TargetID &);
    TargetID *release_TargetID();
    void set_TargetID(TargetID *);

    ClassmarkInformation2 *get_ClassmarkInformation2();
    const ClassmarkInformation2 *get_ClassmarkInformation2() const;
    void set_ClassmarkInformation2(const ClassmarkInformation2 &);
    ClassmarkInformation2 *release_ClassmarkInformation2();
    void set_ClassmarkInformation2(ClassmarkInformation2 *);

    ClassmarkInformation3 *get_ClassmarkInformation3();
    const ClassmarkInformation3 *get_ClassmarkInformation3() const;
    void set_ClassmarkInformation3(const ClassmarkInformation3 &);
    ClassmarkInformation3 *release_ClassmarkInformation3();
    void set_ClassmarkInformation3(ClassmarkInformation3 *);

    SourceRNC_ToTargetRNC_TransparentContainer *get_SourceRNC_ToTargetRNC_TransparentContainer();
    const SourceRNC_ToTargetRNC_TransparentContainer *get_SourceRNC_ToTargetRNC_TransparentContainer() const;
    void set_SourceRNC_ToTargetRNC_TransparentContainer(const SourceRNC_ToTargetRNC_TransparentContainer &);
    SourceRNC_ToTargetRNC_TransparentContainer *release_SourceRNC_ToTargetRNC_TransparentContainer();
    void set_SourceRNC_ToTargetRNC_TransparentContainer(SourceRNC_ToTargetRNC_TransparentContainer *);

    OldBSS_ToNewBSS_Information *get_OldBSS_ToNewBSS_Information();
    const OldBSS_ToNewBSS_Information *get_OldBSS_ToNewBSS_Information() const;
    void set_OldBSS_ToNewBSS_Information(const OldBSS_ToNewBSS_Information &);
    OldBSS_ToNewBSS_Information *release_OldBSS_ToNewBSS_Information();
    void set_OldBSS_ToNewBSS_Information(OldBSS_ToNewBSS_Information *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC RelocationRequiredExtensions_Extension : public OssConstrainedOpenType
{
public:
    RelocationRequiredExtensions_Extension();
    RelocationRequiredExtensions_Extension(const RelocationRequiredExtensions_Extension &);
    ~RelocationRequiredExtensions_Extension();
    RelocationRequiredExtensions_Extension & operator = (const RelocationRequiredExtensions_Extension &);
    int operator == (const RelocationRequiredExtensions_Extension &) const;
    int operator != (const RelocationRequiredExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    GERAN_Classmark *get_GERAN_Classmark();
    const GERAN_Classmark *get_GERAN_Classmark() const;
    void set_GERAN_Classmark(const GERAN_Classmark &);
    GERAN_Classmark *release_GERAN_Classmark();
    void set_GERAN_Classmark(GERAN_Classmark *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq70   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequiredIEs_Value value;

    __seq70();
    __seq70(const __seq70 &);
    __seq70(id, criticality, const value &);

    __seq70 & operator = (const __seq70 &);
    int operator == (const __seq70 &) const;
    int operator != (const __seq70 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared7   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequiredExtensions_Extension extensionValue;

    __shared7();
    __shared7(const __shared7 &);
    __shared7(id, criticality, const extensionValue &);

    __shared7 & operator = (const __shared7 &);
    int operator == (const __shared7 &) const;
    int operator != (const __shared7 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __seqof66;

class OSS_PUBLIC RAB_RelocationReleaseList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof66 component;

    RAB_RelocationReleaseList();
    RAB_RelocationReleaseList(const RAB_RelocationReleaseList &);
    ~RAB_RelocationReleaseList();

    RAB_RelocationReleaseList & operator = (const RAB_RelocationReleaseList &);
    int operator == (const RAB_RelocationReleaseList &) const;
    int operator != (const RAB_RelocationReleaseList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_RelocationReleaseList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_RelocationReleaseList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_RelocationReleaseList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof68;

class OSS_PUBLIC RAB_DataForwardingList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof68 component;

    RAB_DataForwardingList();
    RAB_DataForwardingList(const RAB_DataForwardingList &);
    ~RAB_DataForwardingList();

    RAB_DataForwardingList & operator = (const RAB_DataForwardingList &);
    int operator == (const RAB_DataForwardingList &) const;
    int operator != (const RAB_DataForwardingList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_DataForwardingList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_DataForwardingList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_DataForwardingList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationCommandIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationCommandIEs_Value();
    RelocationCommandIEs_Value(const RelocationCommandIEs_Value &);
    ~RelocationCommandIEs_Value();
    RelocationCommandIEs_Value & operator = (const RelocationCommandIEs_Value &);
    int operator == (const RelocationCommandIEs_Value &) const;
    int operator != (const RelocationCommandIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TargetRNC_ToSourceRNC_TransparentContainer *get_TargetRNC_ToSourceRNC_TransparentContainer();
    const TargetRNC_ToSourceRNC_TransparentContainer *get_TargetRNC_ToSourceRNC_TransparentContainer() const;
    void set_TargetRNC_ToSourceRNC_TransparentContainer(const TargetRNC_ToSourceRNC_TransparentContainer &);
    TargetRNC_ToSourceRNC_TransparentContainer *release_TargetRNC_ToSourceRNC_TransparentContainer();
    void set_TargetRNC_ToSourceRNC_TransparentContainer(TargetRNC_ToSourceRNC_TransparentContainer *);

    L3_Information *get_L3_Information();
    const L3_Information *get_L3_Information() const;
    void set_L3_Information(const L3_Information &);
    L3_Information *release_L3_Information();
    void set_L3_Information(L3_Information *);

    RAB_RelocationReleaseList *get_RAB_RelocationReleaseList();
    const RAB_RelocationReleaseList *get_RAB_RelocationReleaseList() const;
    void set_RAB_RelocationReleaseList(const RAB_RelocationReleaseList &);
    RAB_RelocationReleaseList *release_RAB_RelocationReleaseList();
    void set_RAB_RelocationReleaseList(RAB_RelocationReleaseList *);

    RAB_DataForwardingList *get_RAB_DataForwardingList();
    const RAB_DataForwardingList *get_RAB_DataForwardingList() const;
    void set_RAB_DataForwardingList(const RAB_DataForwardingList &);
    RAB_DataForwardingList *release_RAB_DataForwardingList();
    void set_RAB_DataForwardingList(RAB_DataForwardingList *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC RelocationCommandExtensions_Extension : public OssConstrainedOpenType
{
public:
    RelocationCommandExtensions_Extension();
    RelocationCommandExtensions_Extension(const RelocationCommandExtensions_Extension &);
    ~RelocationCommandExtensions_Extension();
    RelocationCommandExtensions_Extension & operator = (const RelocationCommandExtensions_Extension &);
    int operator == (const RelocationCommandExtensions_Extension &) const;
    int operator != (const RelocationCommandExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InterSystemInformation_TransparentContainer *get_InterSystemInformation_TransparentContainer();
    const InterSystemInformation_TransparentContainer *get_InterSystemInformation_TransparentContainer() const;
    void set_InterSystemInformation_TransparentContainer(const InterSystemInformation_TransparentContainer &);
    InterSystemInformation_TransparentContainer *release_InterSystemInformation_TransparentContainer();
    void set_InterSystemInformation_TransparentContainer(InterSystemInformation_TransparentContainer *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq72   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationCommandIEs_Value value;

    __seq72();
    __seq72(const __seq72 &);
    __seq72(id, criticality, const value &);

    __seq72 & operator = (const __seq72 &);
    int operator == (const __seq72 &) const;
    int operator != (const __seq72 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared32   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationCommandExtensions_Extension extensionValue;

    __shared32();
    __shared32(const __shared32 &);
    __shared32(id, criticality, const extensionValue &);

    __shared32 & operator = (const __shared32 &);
    int operator == (const __shared32 &) const;
    int operator != (const __shared32 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __shared16   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef __shared4 iE_Extensions;

    __shared16();
    __shared16(const __shared16 &);
    __shared16(const rAB_ID &, const iE_Extensions &);
    __shared16(const rAB_ID &);

    __shared16 & operator = (const __shared16 &);
    int operator == (const __shared16 &) const;
    int operator != (const __shared16 &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared16 RAB_DataForwardingItem_SRNS_CtxReq;

typedef __shared16 RAB_RelocationReleaseItem;

class OSS_PUBLIC RAB_RelocationReleaseItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_RelocationReleaseItemIEs_Value();
    RAB_RelocationReleaseItemIEs_Value(const RAB_RelocationReleaseItemIEs_Value &);
    ~RAB_RelocationReleaseItemIEs_Value();
    RAB_RelocationReleaseItemIEs_Value & operator = (const RAB_RelocationReleaseItemIEs_Value &);
    int operator == (const RAB_RelocationReleaseItemIEs_Value &) const;
    int operator != (const RAB_RelocationReleaseItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared16 *get_RAB_RelocationReleaseItem();
    const __shared16 *get_RAB_RelocationReleaseItem() const;
    void set_RAB_RelocationReleaseItem(const __shared16 &);
    __shared16 *release_RAB_RelocationReleaseItem();
    void set_RAB_RelocationReleaseItem(__shared16 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq74;

class OSS_PUBLIC __seqof66 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq74 component;

    __seqof66();
    __seqof66(const __seqof66 &);
    ~__seqof66();

    __seqof66 & operator = (const __seqof66 &);
    int operator == (const __seqof66 &) const;
    int operator != (const __seqof66 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof66 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof66 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof66 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq74   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_RelocationReleaseItemIEs_Value value;

    __seq74();
    __seq74(const __seq74 &);
    __seq74(id, criticality, const value &);

    __seq74 & operator = (const __seq74 &);
    int operator == (const __seq74 &) const;
    int operator != (const __seq74 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq77;

class OSS_PUBLIC __seqof69 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq77 component;

    __seqof69();
    __seqof69(const __seqof69 &);
    ~__seqof69();

    __seqof69 & operator = (const __seqof69 &);
    int operator == (const __seqof69 &) const;
    int operator != (const __seqof69 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof69 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof69 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof69 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_DataForwardingItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OssBitString transportLayerAddress;
    typedef IuTransportAssociation iuTransportAssociation;
    typedef __seqof69 iE_Extensions;

    RAB_DataForwardingItem();
    RAB_DataForwardingItem(const RAB_DataForwardingItem &);
    RAB_DataForwardingItem(const rAB_ID &, const transportLayerAddress &, const iuTransportAssociation &, 
	const iE_Extensions &);
    RAB_DataForwardingItem(const rAB_ID &, const transportLayerAddress &, const iuTransportAssociation &);

    RAB_DataForwardingItem & operator = (const RAB_DataForwardingItem &);
    int operator == (const RAB_DataForwardingItem &) const;
    int operator != (const RAB_DataForwardingItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    transportLayerAddress & get_transportLayerAddress();
    const transportLayerAddress & get_transportLayerAddress() const;
    void set_transportLayerAddress(const transportLayerAddress &);

    iuTransportAssociation & get_iuTransportAssociation();
    const iuTransportAssociation & get_iuTransportAssociation() const;
    void set_iuTransportAssociation(const iuTransportAssociation &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    transportLayerAddress transportLayerAddress_field;
    iuTransportAssociation iuTransportAssociation_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_DataForwardingItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_DataForwardingItemIEs_Value();
    RAB_DataForwardingItemIEs_Value(const RAB_DataForwardingItemIEs_Value &);
    ~RAB_DataForwardingItemIEs_Value();
    RAB_DataForwardingItemIEs_Value & operator = (const RAB_DataForwardingItemIEs_Value &);
    int operator == (const RAB_DataForwardingItemIEs_Value &) const;
    int operator != (const RAB_DataForwardingItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataForwardingItem *get_RAB_DataForwardingItem();
    const RAB_DataForwardingItem *get_RAB_DataForwardingItem() const;
    void set_RAB_DataForwardingItem(const RAB_DataForwardingItem &);
    RAB_DataForwardingItem *release_RAB_DataForwardingItem();
    void set_RAB_DataForwardingItem(RAB_DataForwardingItem *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq76;

class OSS_PUBLIC __seqof68 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq76 component;

    __seqof68();
    __seqof68(const __seqof68 &);
    ~__seqof68();

    __seqof68 & operator = (const __seqof68 &);
    int operator == (const __seqof68 &) const;
    int operator != (const __seqof68 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof68 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof68 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof68 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq76   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_DataForwardingItemIEs_Value value;

    __seq76();
    __seq76(const __seq76 &);
    __seq76(id, criticality, const value &);

    __seq76 & operator = (const __seq76 &);
    int operator == (const __seq76 &) const;
    int operator != (const __seq76 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_DataForwardingItem_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_DataForwardingItem_ExtIEs_Extension();
    RAB_DataForwardingItem_ExtIEs_Extension(const RAB_DataForwardingItem_ExtIEs_Extension &);
    ~RAB_DataForwardingItem_ExtIEs_Extension();
    RAB_DataForwardingItem_ExtIEs_Extension & operator = (const RAB_DataForwardingItem_ExtIEs_Extension &);
    int operator == (const RAB_DataForwardingItem_ExtIEs_Extension &) const;
    int operator != (const RAB_DataForwardingItem_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TransportLayerAddress *get_TransportLayerAddress();
    const TransportLayerAddress *get_TransportLayerAddress() const;
    void set_TransportLayerAddress(const TransportLayerAddress &);
    TransportLayerAddress *release_TransportLayerAddress();
    void set_TransportLayerAddress(TransportLayerAddress *);

    IuTransportAssociation *get_IuTransportAssociation();
    const IuTransportAssociation *get_IuTransportAssociation() const;
    void set_IuTransportAssociation(const IuTransportAssociation &);
    IuTransportAssociation *release_IuTransportAssociation();
    void set_IuTransportAssociation(IuTransportAssociation *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq77   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_DataForwardingItem_ExtIEs_Extension extensionValue;

    __seq77();
    __seq77(const __seq77 &);
    __seq77(id, criticality, const extensionValue &);

    __seq77 & operator = (const __seq77 &);
    int operator == (const __seq77 &) const;
    int operator != (const __seq77 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC RelocationPreparationFailureIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationPreparationFailureIEs_Value();
    RelocationPreparationFailureIEs_Value(const RelocationPreparationFailureIEs_Value &);
    ~RelocationPreparationFailureIEs_Value();
    RelocationPreparationFailureIEs_Value & operator = (const RelocationPreparationFailureIEs_Value &);
    int operator == (const RelocationPreparationFailureIEs_Value &) const;
    int operator != (const RelocationPreparationFailureIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __shared35   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationPreparationFailureIEs_Value value;

    __shared35();
    __shared35(const __shared35 &);
    __shared35(id, criticality, const value &);

    __shared35 & operator = (const __shared35 &);
    int operator == (const __shared35 &) const;
    int operator != (const __shared35 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof74;

class OSS_PUBLIC RAB_SetupList_RelocReq : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof74 component;

    RAB_SetupList_RelocReq();
    RAB_SetupList_RelocReq(const RAB_SetupList_RelocReq &);
    ~RAB_SetupList_RelocReq();

    RAB_SetupList_RelocReq & operator = (const RAB_SetupList_RelocReq &);
    int operator == (const RAB_SetupList_RelocReq &) const;
    int operator != (const RAB_SetupList_RelocReq &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_SetupList_RelocReq *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_SetupList_RelocReq *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_SetupList_RelocReq *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RelocationRequestIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationRequestIEs_Value();
    RelocationRequestIEs_Value(const RelocationRequestIEs_Value &);
    ~RelocationRequestIEs_Value();
    RelocationRequestIEs_Value & operator = (const RelocationRequestIEs_Value &);
    int operator == (const RelocationRequestIEs_Value &) const;
    int operator != (const RelocationRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    PermanentNAS_UE_ID *get_PermanentNAS_UE_ID();
    const PermanentNAS_UE_ID *get_PermanentNAS_UE_ID() const;
    void set_PermanentNAS_UE_ID(const PermanentNAS_UE_ID &);
    PermanentNAS_UE_ID *release_PermanentNAS_UE_ID();
    void set_PermanentNAS_UE_ID(PermanentNAS_UE_ID *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    SourceRNC_ToTargetRNC_TransparentContainer *get_SourceRNC_ToTargetRNC_TransparentContainer();
    const SourceRNC_ToTargetRNC_TransparentContainer *get_SourceRNC_ToTargetRNC_TransparentContainer() const;
    void set_SourceRNC_ToTargetRNC_TransparentContainer(const SourceRNC_ToTargetRNC_TransparentContainer &);
    SourceRNC_ToTargetRNC_TransparentContainer *release_SourceRNC_ToTargetRNC_TransparentContainer();
    void set_SourceRNC_ToTargetRNC_TransparentContainer(SourceRNC_ToTargetRNC_TransparentContainer *);

    RAB_SetupList_RelocReq *get_RAB_SetupList_RelocReq();
    const RAB_SetupList_RelocReq *get_RAB_SetupList_RelocReq() const;
    void set_RAB_SetupList_RelocReq(const RAB_SetupList_RelocReq &);
    RAB_SetupList_RelocReq *release_RAB_SetupList_RelocReq();
    void set_RAB_SetupList_RelocReq(RAB_SetupList_RelocReq *);

    __shared15 *get_IntegrityProtectionInformation();
    const __shared15 *get_IntegrityProtectionInformation() const;
    void set_IntegrityProtectionInformation(const __shared15 &);
    __shared15 *release_IntegrityProtectionInformation();
    void set_IntegrityProtectionInformation(__shared15 *);

    __shared15 *get_EncryptionInformation();
    const __shared15 *get_EncryptionInformation() const;
    void set_EncryptionInformation(const __shared15 &);
    __shared15 *release_EncryptionInformation();
    void set_EncryptionInformation(__shared15 *);

    IuSignallingConnectionIdentifier *get_IuSignallingConnectionIdentifier();
    const IuSignallingConnectionIdentifier *get_IuSignallingConnectionIdentifier() const;
    void set_IuSignallingConnectionIdentifier(const IuSignallingConnectionIdentifier &);
    IuSignallingConnectionIdentifier *release_IuSignallingConnectionIdentifier();
    void set_IuSignallingConnectionIdentifier(IuSignallingConnectionIdentifier *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC RelocationRequestExtensions_Extension : public OssConstrainedOpenType
{
public:
    RelocationRequestExtensions_Extension();
    RelocationRequestExtensions_Extension(const RelocationRequestExtensions_Extension &);
    ~RelocationRequestExtensions_Extension();
    RelocationRequestExtensions_Extension & operator = (const RelocationRequestExtensions_Extension &);
    int operator == (const RelocationRequestExtensions_Extension &) const;
    int operator != (const RelocationRequestExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);

    SNA_Access_Information *get_SNA_Access_Information();
    const SNA_Access_Information *get_SNA_Access_Information() const;
    void set_SNA_Access_Information(const SNA_Access_Information &);
    SNA_Access_Information *release_SNA_Access_Information();
    void set_SNA_Access_Information(SNA_Access_Information *);

    UESBI_Iu *get_UESBI_Iu();
    const UESBI_Iu *get_UESBI_Iu() const;
    void set_UESBI_Iu(const UESBI_Iu &);
    UESBI_Iu *release_UESBI_Iu();
    void set_UESBI_Iu(UESBI_Iu *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq80   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequestIEs_Value value;

    __seq80();
    __seq80(const __seq80 &);
    __seq80(id, criticality, const value &);

    __seq80 & operator = (const __seq80 &);
    int operator == (const __seq80 &) const;
    int operator != (const __seq80 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq81   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequestExtensions_Extension extensionValue;

    __seq81();
    __seq81(const __seq81 &);
    __seq81(id, criticality, const extensionValue &);

    __seq81 & operator = (const __seq81 &);
    int operator == (const __seq81 &) const;
    int operator != (const __seq81 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC RAB_SetupItem_RelocReq   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OssBitString nAS_SynchronisationIndicator;
    typedef RAB_Parameters rAB_Parameters;
    typedef enum DataVolumeReportingIndication dataVolumeReportingIndication;
    typedef PDP_TypeInformation pDP_TypeInformation;
    typedef UserPlaneInformation userPlaneInformation;
    typedef OssBitString transportLayerAddress;
    typedef IuTransportAssociation iuTransportAssociation;
    typedef enum Service_Handover service_Handover;
    typedef __shared14 iE_Extensions;

    RAB_SetupItem_RelocReq();
    RAB_SetupItem_RelocReq(const RAB_SetupItem_RelocReq &);
    RAB_SetupItem_RelocReq(const rAB_ID &, const nAS_SynchronisationIndicator &, 
	const rAB_Parameters &, dataVolumeReportingIndication, const pDP_TypeInformation &, 
	const userPlaneInformation &, const transportLayerAddress &, const iuTransportAssociation &, 
	service_Handover, const iE_Extensions &);
    RAB_SetupItem_RelocReq(const rAB_ID &, const rAB_Parameters &, const userPlaneInformation &, 
	const transportLayerAddress &, const iuTransportAssociation &);

    RAB_SetupItem_RelocReq & operator = (const RAB_SetupItem_RelocReq &);
    int operator == (const RAB_SetupItem_RelocReq &) const;
    int operator != (const RAB_SetupItem_RelocReq &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    nAS_SynchronisationIndicator *get_nAS_SynchronisationIndicator();
    const nAS_SynchronisationIndicator *get_nAS_SynchronisationIndicator() const;
    void set_nAS_SynchronisationIndicator(const nAS_SynchronisationIndicator &);
    int nAS_SynchronisationIndicator_is_present() const;
    void omit_nAS_SynchronisationIndicator();

    rAB_Parameters & get_rAB_Parameters();
    const rAB_Parameters & get_rAB_Parameters() const;
    void set_rAB_Parameters(const rAB_Parameters &);

    dataVolumeReportingIndication *get_dataVolumeReportingIndication();
    const dataVolumeReportingIndication *get_dataVolumeReportingIndication() const;
    void set_dataVolumeReportingIndication(dataVolumeReportingIndication);
    int dataVolumeReportingIndication_is_present() const;
    void omit_dataVolumeReportingIndication();

    pDP_TypeInformation *get_pDP_TypeInformation();
    const pDP_TypeInformation *get_pDP_TypeInformation() const;
    void set_pDP_TypeInformation(const pDP_TypeInformation &);
    int pDP_TypeInformation_is_present() const;
    void omit_pDP_TypeInformation();

    userPlaneInformation & get_userPlaneInformation();
    const userPlaneInformation & get_userPlaneInformation() const;
    void set_userPlaneInformation(const userPlaneInformation &);

    transportLayerAddress & get_transportLayerAddress();
    const transportLayerAddress & get_transportLayerAddress() const;
    void set_transportLayerAddress(const transportLayerAddress &);

    iuTransportAssociation & get_iuTransportAssociation();
    const iuTransportAssociation & get_iuTransportAssociation() const;
    void set_iuTransportAssociation(const iuTransportAssociation &);

    service_Handover *get_service_Handover();
    const service_Handover *get_service_Handover() const;
    void set_service_Handover(service_Handover);
    int service_Handover_is_present() const;
    void omit_service_Handover();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    nAS_SynchronisationIndicator nAS_SynchronisationIndicator_field;
    rAB_Parameters rAB_Parameters_field;
    dataVolumeReportingIndication dataVolumeReportingIndication_field;
    pDP_TypeInformation pDP_TypeInformation_field;
    userPlaneInformation userPlaneInformation_field;
    transportLayerAddress transportLayerAddress_field;
    iuTransportAssociation iuTransportAssociation_field;
    service_Handover service_Handover_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupItem_RelocReq_IEs_Value : public OssConstrainedOpenType
{
public:
    RAB_SetupItem_RelocReq_IEs_Value();
    RAB_SetupItem_RelocReq_IEs_Value(const RAB_SetupItem_RelocReq_IEs_Value &);
    ~RAB_SetupItem_RelocReq_IEs_Value();
    RAB_SetupItem_RelocReq_IEs_Value & operator = (const RAB_SetupItem_RelocReq_IEs_Value &);
    int operator == (const RAB_SetupItem_RelocReq_IEs_Value &) const;
    int operator != (const RAB_SetupItem_RelocReq_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupItem_RelocReq *get_RAB_SetupItem_RelocReq();
    const RAB_SetupItem_RelocReq *get_RAB_SetupItem_RelocReq() const;
    void set_RAB_SetupItem_RelocReq(const RAB_SetupItem_RelocReq &);
    RAB_SetupItem_RelocReq *release_RAB_SetupItem_RelocReq();
    void set_RAB_SetupItem_RelocReq(RAB_SetupItem_RelocReq *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq82;

class OSS_PUBLIC __seqof74 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq82 component;

    __seqof74();
    __seqof74(const __seqof74 &);
    ~__seqof74();

    __seqof74 & operator = (const __seqof74 &);
    int operator == (const __seqof74 &) const;
    int operator != (const __seqof74 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof74 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof74 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof74 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq82   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupItem_RelocReq_IEs_Value value;

    __seq82();
    __seq82(const __seq82 &);
    __seq82(id, criticality, const value &);

    __seq82 & operator = (const __seq82 &);
    int operator == (const __seq82 &) const;
    int operator != (const __seq82 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_SetupItem_RelocReq_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_SetupItem_RelocReq_ExtIEs_Extension();
    RAB_SetupItem_RelocReq_ExtIEs_Extension(const RAB_SetupItem_RelocReq_ExtIEs_Extension &);
    ~RAB_SetupItem_RelocReq_ExtIEs_Extension();
    RAB_SetupItem_RelocReq_ExtIEs_Extension & operator = (const RAB_SetupItem_RelocReq_ExtIEs_Extension &);
    int operator == (const RAB_SetupItem_RelocReq_ExtIEs_Extension &) const;
    int operator != (const RAB_SetupItem_RelocReq_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Alt_RAB_Parameters *get_Alt_RAB_Parameters();
    const Alt_RAB_Parameters *get_Alt_RAB_Parameters() const;
    void set_Alt_RAB_Parameters(const Alt_RAB_Parameters &);
    Alt_RAB_Parameters *release_Alt_RAB_Parameters();
    void set_Alt_RAB_Parameters(Alt_RAB_Parameters *);

    GERAN_BSC_Container *get_GERAN_BSC_Container();
    const GERAN_BSC_Container *get_GERAN_BSC_Container() const;
    void set_GERAN_BSC_Container(const GERAN_BSC_Container &);
    GERAN_BSC_Container *release_GERAN_BSC_Container();
    void set_GERAN_BSC_Container(GERAN_BSC_Container *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __shared13   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupItem_RelocReq_ExtIEs_Extension extensionValue;

    __shared13();
    __shared13(const __shared13 &);
    __shared13(id, criticality, const extensionValue &);

    __shared13 & operator = (const __shared13 &);
    int operator == (const __shared13 &) const;
    int operator != (const __shared13 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __seqof79;

class OSS_PUBLIC RAB_SetupList_RelocReqAck : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof79 component;

    RAB_SetupList_RelocReqAck();
    RAB_SetupList_RelocReqAck(const RAB_SetupList_RelocReqAck &);
    ~RAB_SetupList_RelocReqAck();

    RAB_SetupList_RelocReqAck & operator = (const RAB_SetupList_RelocReqAck &);
    int operator == (const RAB_SetupList_RelocReqAck &) const;
    int operator != (const RAB_SetupList_RelocReqAck &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_SetupList_RelocReqAck *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_SetupList_RelocReqAck *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_SetupList_RelocReqAck *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof81;

class OSS_PUBLIC __shared34 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof81 component;

    __shared34();
    __shared34(const __shared34 &);
    ~__shared34();

    __shared34 & operator = (const __shared34 &);
    int operator == (const __shared34 &) const;
    int operator != (const __shared34 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared34 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared34 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared34 *extract_after(OssIndex, OssIndex);
};

typedef __shared34 RAB_FailedList;

class OSS_PUBLIC RelocationRequestAcknowledgeIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationRequestAcknowledgeIEs_Value();
    RelocationRequestAcknowledgeIEs_Value(const RelocationRequestAcknowledgeIEs_Value &);
    ~RelocationRequestAcknowledgeIEs_Value();
    RelocationRequestAcknowledgeIEs_Value & operator = (const RelocationRequestAcknowledgeIEs_Value &);
    int operator == (const RelocationRequestAcknowledgeIEs_Value &) const;
    int operator != (const RelocationRequestAcknowledgeIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TargetRNC_ToSourceRNC_TransparentContainer *get_TargetRNC_ToSourceRNC_TransparentContainer();
    const TargetRNC_ToSourceRNC_TransparentContainer *get_TargetRNC_ToSourceRNC_TransparentContainer() const;
    void set_TargetRNC_ToSourceRNC_TransparentContainer(const TargetRNC_ToSourceRNC_TransparentContainer &);
    TargetRNC_ToSourceRNC_TransparentContainer *release_TargetRNC_ToSourceRNC_TransparentContainer();
    void set_TargetRNC_ToSourceRNC_TransparentContainer(TargetRNC_ToSourceRNC_TransparentContainer *);

    RAB_SetupList_RelocReqAck *get_RAB_SetupList_RelocReqAck();
    const RAB_SetupList_RelocReqAck *get_RAB_SetupList_RelocReqAck() const;
    void set_RAB_SetupList_RelocReqAck(const RAB_SetupList_RelocReqAck &);
    RAB_SetupList_RelocReqAck *release_RAB_SetupList_RelocReqAck();
    void set_RAB_SetupList_RelocReqAck(RAB_SetupList_RelocReqAck *);

    __shared34 *get_RAB_FailedList();
    const __shared34 *get_RAB_FailedList() const;
    void set_RAB_FailedList(const __shared34 &);
    __shared34 *release_RAB_FailedList();
    void set_RAB_FailedList(__shared34 *);

    ChosenIntegrityProtectionAlgorithm *get_ChosenIntegrityProtectionAlgorithm();
    const ChosenIntegrityProtectionAlgorithm *get_ChosenIntegrityProtectionAlgorithm() const;
    void set_ChosenIntegrityProtectionAlgorithm(const ChosenIntegrityProtectionAlgorithm &);
    ChosenIntegrityProtectionAlgorithm *release_ChosenIntegrityProtectionAlgorithm();
    void set_ChosenIntegrityProtectionAlgorithm(ChosenIntegrityProtectionAlgorithm *);

    ChosenEncryptionAlgorithm *get_ChosenEncryptionAlgorithm();
    const ChosenEncryptionAlgorithm *get_ChosenEncryptionAlgorithm() const;
    void set_ChosenEncryptionAlgorithm(const ChosenEncryptionAlgorithm &);
    ChosenEncryptionAlgorithm *release_ChosenEncryptionAlgorithm();
    void set_ChosenEncryptionAlgorithm(ChosenEncryptionAlgorithm *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC RelocationRequestAcknowledgeExtensions_Extension : public OssConstrainedOpenType
{
public:
    RelocationRequestAcknowledgeExtensions_Extension();
    RelocationRequestAcknowledgeExtensions_Extension(const RelocationRequestAcknowledgeExtensions_Extension &);
    ~RelocationRequestAcknowledgeExtensions_Extension();
    RelocationRequestAcknowledgeExtensions_Extension & operator = (const RelocationRequestAcknowledgeExtensions_Extension &);
    int operator == (const RelocationRequestAcknowledgeExtensions_Extension &) const;
    int operator != (const RelocationRequestAcknowledgeExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    NewBSS_To_OldBSS_Information *get_NewBSS_To_OldBSS_Information();
    const NewBSS_To_OldBSS_Information *get_NewBSS_To_OldBSS_Information() const;
    void set_NewBSS_To_OldBSS_Information(const NewBSS_To_OldBSS_Information &);
    NewBSS_To_OldBSS_Information *release_NewBSS_To_OldBSS_Information();
    void set_NewBSS_To_OldBSS_Information(NewBSS_To_OldBSS_Information *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq85   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequestAcknowledgeIEs_Value value;

    __seq85();
    __seq85(const __seq85 &);
    __seq85(id, criticality, const value &);

    __seq85 & operator = (const __seq85 &);
    int operator == (const __seq85 &) const;
    int operator != (const __seq85 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq86   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationRequestAcknowledgeExtensions_Extension extensionValue;

    __seq86();
    __seq86(const __seq86 &);
    __seq86(id, criticality, const extensionValue &);

    __seq86 & operator = (const __seq86 &);
    int operator == (const __seq86 &) const;
    int operator != (const __seq86 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __seq88;

class OSS_PUBLIC __seqof80 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq88 component;

    __seqof80();
    __seqof80(const __seqof80 &);
    ~__seqof80();

    __seqof80 & operator = (const __seqof80 &);
    int operator == (const __seqof80 &) const;
    int operator != (const __seqof80 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof80 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof80 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof80 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_SetupItem_RelocReqAck   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OssBitString transportLayerAddress;
    typedef IuTransportAssociation iuTransportAssociation;
    typedef __seqof80 iE_Extensions;

    RAB_SetupItem_RelocReqAck();
    RAB_SetupItem_RelocReqAck(const RAB_SetupItem_RelocReqAck &);
    RAB_SetupItem_RelocReqAck(const rAB_ID &, const transportLayerAddress &, const iuTransportAssociation &, 
	const iE_Extensions &);
    RAB_SetupItem_RelocReqAck(const rAB_ID &);

    RAB_SetupItem_RelocReqAck & operator = (const RAB_SetupItem_RelocReqAck &);
    int operator == (const RAB_SetupItem_RelocReqAck &) const;
    int operator != (const RAB_SetupItem_RelocReqAck &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    transportLayerAddress *get_transportLayerAddress();
    const transportLayerAddress *get_transportLayerAddress() const;
    void set_transportLayerAddress(const transportLayerAddress &);
    int transportLayerAddress_is_present() const;
    void omit_transportLayerAddress();

    iuTransportAssociation *get_iuTransportAssociation();
    const iuTransportAssociation *get_iuTransportAssociation() const;
    void set_iuTransportAssociation(const iuTransportAssociation &);
    int iuTransportAssociation_is_present() const;
    void omit_iuTransportAssociation();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    transportLayerAddress transportLayerAddress_field;
    iuTransportAssociation iuTransportAssociation_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupItem_RelocReqAck_IEs_Value : public OssConstrainedOpenType
{
public:
    RAB_SetupItem_RelocReqAck_IEs_Value();
    RAB_SetupItem_RelocReqAck_IEs_Value(const RAB_SetupItem_RelocReqAck_IEs_Value &);
    ~RAB_SetupItem_RelocReqAck_IEs_Value();
    RAB_SetupItem_RelocReqAck_IEs_Value & operator = (const RAB_SetupItem_RelocReqAck_IEs_Value &);
    int operator == (const RAB_SetupItem_RelocReqAck_IEs_Value &) const;
    int operator != (const RAB_SetupItem_RelocReqAck_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupItem_RelocReqAck *get_RAB_SetupItem_RelocReqAck();
    const RAB_SetupItem_RelocReqAck *get_RAB_SetupItem_RelocReqAck() const;
    void set_RAB_SetupItem_RelocReqAck(const RAB_SetupItem_RelocReqAck &);
    RAB_SetupItem_RelocReqAck *release_RAB_SetupItem_RelocReqAck();
    void set_RAB_SetupItem_RelocReqAck(RAB_SetupItem_RelocReqAck *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq87;

class OSS_PUBLIC __seqof79 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq87 component;

    __seqof79();
    __seqof79(const __seqof79 &);
    ~__seqof79();

    __seqof79 & operator = (const __seqof79 &);
    int operator == (const __seqof79 &) const;
    int operator != (const __seqof79 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof79 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof79 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof79 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq87   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupItem_RelocReqAck_IEs_Value value;

    __seq87();
    __seq87(const __seq87 &);
    __seq87(id, criticality, const value &);

    __seq87 & operator = (const __seq87 &);
    int operator == (const __seq87 &) const;
    int operator != (const __seq87 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_SetupItem_RelocReqAck_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_SetupItem_RelocReqAck_ExtIEs_Extension();
    RAB_SetupItem_RelocReqAck_ExtIEs_Extension(const RAB_SetupItem_RelocReqAck_ExtIEs_Extension &);
    ~RAB_SetupItem_RelocReqAck_ExtIEs_Extension();
    RAB_SetupItem_RelocReqAck_ExtIEs_Extension & operator = (const RAB_SetupItem_RelocReqAck_ExtIEs_Extension &);
    int operator == (const RAB_SetupItem_RelocReqAck_ExtIEs_Extension &) const;
    int operator != (const RAB_SetupItem_RelocReqAck_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Ass_RAB_Parameters *get_Ass_RAB_Parameters();
    const Ass_RAB_Parameters *get_Ass_RAB_Parameters() const;
    void set_Ass_RAB_Parameters(const Ass_RAB_Parameters &);
    Ass_RAB_Parameters *release_Ass_RAB_Parameters();
    void set_Ass_RAB_Parameters(Ass_RAB_Parameters *);

    TransportLayerAddress *get_TransportLayerAddress();
    const TransportLayerAddress *get_TransportLayerAddress() const;
    void set_TransportLayerAddress(const TransportLayerAddress &);
    TransportLayerAddress *release_TransportLayerAddress();
    void set_TransportLayerAddress(TransportLayerAddress *);

    IuTransportAssociation *get_IuTransportAssociation();
    const IuTransportAssociation *get_IuTransportAssociation() const;
    void set_IuTransportAssociation(const IuTransportAssociation &);
    IuTransportAssociation *release_IuTransportAssociation();
    void set_IuTransportAssociation(IuTransportAssociation *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq88   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupItem_RelocReqAck_ExtIEs_Extension extensionValue;

    __seq88();
    __seq88(const __seq88 &);
    __seq88(id, criticality, const extensionValue &);

    __seq88 & operator = (const __seq88 &);
    int operator == (const __seq88 &) const;
    int operator != (const __seq88 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __shared20   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef Cause cause;
    typedef __shared4 iE_Extensions;

    __shared20();
    __shared20(const __shared20 &);
    __shared20(const rAB_ID &, const cause &, const iE_Extensions &);
    __shared20(const rAB_ID &, const cause &);

    __shared20 & operator = (const __shared20 &);
    int operator == (const __shared20 &) const;
    int operator != (const __shared20 &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    cause & get_cause();
    const cause & get_cause() const;
    void set_cause(const cause &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    cause cause_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared20 RAB_ReleaseItem;

typedef __shared20 RAB_FailedItem;

class OSS_PUBLIC RAB_FailedItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_FailedItemIEs_Value();
    RAB_FailedItemIEs_Value(const RAB_FailedItemIEs_Value &);
    ~RAB_FailedItemIEs_Value();
    RAB_FailedItemIEs_Value & operator = (const RAB_FailedItemIEs_Value &);
    int operator == (const RAB_FailedItemIEs_Value &) const;
    int operator != (const RAB_FailedItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared20 *get_RAB_FailedItem();
    const __shared20 *get_RAB_FailedItem() const;
    void set_RAB_FailedItem(const __shared20 &);
    __shared20 *release_RAB_FailedItem();
    void set_RAB_FailedItem(__shared20 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq89;

class OSS_PUBLIC __seqof81 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq89 component;

    __seqof81();
    __seqof81(const __seqof81 &);
    ~__seqof81();

    __seqof81 & operator = (const __seqof81 &);
    int operator == (const __seqof81 &) const;
    int operator != (const __seqof81 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof81 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof81 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof81 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq89   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_FailedItemIEs_Value value;

    __seq89();
    __seq89(const __seq89 &);
    __seq89(id, criticality, const value &);

    __seq89 & operator = (const __seq89 &);
    int operator == (const __seq89 &) const;
    int operator != (const __seq89 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RelocationFailureExtensions_Extension : public OssConstrainedOpenType
{
public:
    RelocationFailureExtensions_Extension();
    RelocationFailureExtensions_Extension(const RelocationFailureExtensions_Extension &);
    ~RelocationFailureExtensions_Extension();
    RelocationFailureExtensions_Extension & operator = (const RelocationFailureExtensions_Extension &);
    int operator == (const RelocationFailureExtensions_Extension &) const;
    int operator != (const RelocationFailureExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    NewBSS_To_OldBSS_Information *get_NewBSS_To_OldBSS_Information();
    const NewBSS_To_OldBSS_Information *get_NewBSS_To_OldBSS_Information() const;
    void set_NewBSS_To_OldBSS_Information(const NewBSS_To_OldBSS_Information &);
    NewBSS_To_OldBSS_Information *release_NewBSS_To_OldBSS_Information();
    void set_NewBSS_To_OldBSS_Information(NewBSS_To_OldBSS_Information *);

    GERAN_Classmark *get_GERAN_Classmark();
    const GERAN_Classmark *get_GERAN_Classmark() const;
    void set_GERAN_Classmark(const GERAN_Classmark &);
    GERAN_Classmark *release_GERAN_Classmark();
    void set_GERAN_Classmark(GERAN_Classmark *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq92   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationFailureExtensions_Extension extensionValue;

    __seq92();
    __seq92(const __seq92 &);
    __seq92(id, criticality, const extensionValue &);

    __seq92 & operator = (const __seq92 &);
    int operator == (const __seq92 &) const;
    int operator != (const __seq92 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC RelocationCancelAcknowledgeIEs_Value : public OssConstrainedOpenType
{
public:
    RelocationCancelAcknowledgeIEs_Value();
    RelocationCancelAcknowledgeIEs_Value(const RelocationCancelAcknowledgeIEs_Value &);
    ~RelocationCancelAcknowledgeIEs_Value();
    RelocationCancelAcknowledgeIEs_Value & operator = (const RelocationCancelAcknowledgeIEs_Value &);
    int operator == (const RelocationCancelAcknowledgeIEs_Value &) const;
    int operator != (const RelocationCancelAcknowledgeIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq95   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationCancelAcknowledgeIEs_Value value;

    __seq95();
    __seq95(const __seq95 &);
    __seq95(id, criticality, const value &);

    __seq95 & operator = (const __seq95 &);
    int operator == (const __seq95 &) const;
    int operator != (const __seq95 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof91;

class OSS_PUBLIC RAB_DataForwardingList_SRNS_CtxReq : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof91 component;

    RAB_DataForwardingList_SRNS_CtxReq();
    RAB_DataForwardingList_SRNS_CtxReq(const RAB_DataForwardingList_SRNS_CtxReq &);
    ~RAB_DataForwardingList_SRNS_CtxReq();

    RAB_DataForwardingList_SRNS_CtxReq & operator = (const RAB_DataForwardingList_SRNS_CtxReq &);
    int operator == (const RAB_DataForwardingList_SRNS_CtxReq &) const;
    int operator != (const RAB_DataForwardingList_SRNS_CtxReq &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_DataForwardingList_SRNS_CtxReq *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_DataForwardingList_SRNS_CtxReq *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_DataForwardingList_SRNS_CtxReq *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SRNS_ContextRequestIEs_Value : public OssConstrainedOpenType
{
public:
    SRNS_ContextRequestIEs_Value();
    SRNS_ContextRequestIEs_Value(const SRNS_ContextRequestIEs_Value &);
    ~SRNS_ContextRequestIEs_Value();
    SRNS_ContextRequestIEs_Value & operator = (const SRNS_ContextRequestIEs_Value &);
    int operator == (const SRNS_ContextRequestIEs_Value &) const;
    int operator != (const SRNS_ContextRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataForwardingList_SRNS_CtxReq *get_RAB_DataForwardingList_SRNS_CtxReq();
    const RAB_DataForwardingList_SRNS_CtxReq *get_RAB_DataForwardingList_SRNS_CtxReq() const;
    void set_RAB_DataForwardingList_SRNS_CtxReq(const RAB_DataForwardingList_SRNS_CtxReq &);
    RAB_DataForwardingList_SRNS_CtxReq *release_RAB_DataForwardingList_SRNS_CtxReq();
    void set_RAB_DataForwardingList_SRNS_CtxReq(RAB_DataForwardingList_SRNS_CtxReq *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq97   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SRNS_ContextRequestIEs_Value value;

    __seq97();
    __seq97(const __seq97 &);
    __seq97(id, criticality, const value &);

    __seq97 & operator = (const __seq97 &);
    int operator == (const __seq97 &) const;
    int operator != (const __seq97 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value : public OssConstrainedOpenType
{
public:
    RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value();
    RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value(const RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value &);
    ~RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value();
    RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value & operator = (const RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value &);
    int operator == (const RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value &) const;
    int operator != (const RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared16 *get_RAB_DataForwardingItem_SRNS_CtxReq();
    const __shared16 *get_RAB_DataForwardingItem_SRNS_CtxReq() const;
    void set_RAB_DataForwardingItem_SRNS_CtxReq(const __shared16 &);
    __shared16 *release_RAB_DataForwardingItem_SRNS_CtxReq();
    void set_RAB_DataForwardingItem_SRNS_CtxReq(__shared16 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq99;

class OSS_PUBLIC __seqof91 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq99 component;

    __seqof91();
    __seqof91(const __seqof91 &);
    ~__seqof91();

    __seqof91 & operator = (const __seqof91 &);
    int operator == (const __seqof91 &) const;
    int operator != (const __seqof91 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof91 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof91 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof91 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq99   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_DataForwardingItem_SRNS_CtxReq_IEs_Value value;

    __seq99();
    __seq99(const __seq99 &);
    __seq99(id, criticality, const value &);

    __seq99 & operator = (const __seq99 &);
    int operator == (const __seq99 &) const;
    int operator != (const __seq99 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof95;

class OSS_PUBLIC RAB_ContextList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof95 component;

    RAB_ContextList();
    RAB_ContextList(const RAB_ContextList &);
    ~RAB_ContextList();

    RAB_ContextList & operator = (const RAB_ContextList &);
    int operator == (const RAB_ContextList &) const;
    int operator != (const RAB_ContextList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ContextList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ContextList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ContextList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof97;

class OSS_PUBLIC RAB_ContextFailedtoTransferList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof97 component;

    RAB_ContextFailedtoTransferList();
    RAB_ContextFailedtoTransferList(const RAB_ContextFailedtoTransferList &);
    ~RAB_ContextFailedtoTransferList();

    RAB_ContextFailedtoTransferList & operator = (const RAB_ContextFailedtoTransferList &);
    int operator == (const RAB_ContextFailedtoTransferList &) const;
    int operator != (const RAB_ContextFailedtoTransferList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ContextFailedtoTransferList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ContextFailedtoTransferList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ContextFailedtoTransferList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC SRNS_ContextResponseIEs_Value : public OssConstrainedOpenType
{
public:
    SRNS_ContextResponseIEs_Value();
    SRNS_ContextResponseIEs_Value(const SRNS_ContextResponseIEs_Value &);
    ~SRNS_ContextResponseIEs_Value();
    SRNS_ContextResponseIEs_Value & operator = (const SRNS_ContextResponseIEs_Value &);
    int operator == (const SRNS_ContextResponseIEs_Value &) const;
    int operator != (const SRNS_ContextResponseIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ContextList *get_RAB_ContextList();
    const RAB_ContextList *get_RAB_ContextList() const;
    void set_RAB_ContextList(const RAB_ContextList &);
    RAB_ContextList *release_RAB_ContextList();
    void set_RAB_ContextList(RAB_ContextList *);

    RAB_ContextFailedtoTransferList *get_RAB_ContextFailedtoTransferList();
    const RAB_ContextFailedtoTransferList *get_RAB_ContextFailedtoTransferList() const;
    void set_RAB_ContextFailedtoTransferList(const RAB_ContextFailedtoTransferList &);
    RAB_ContextFailedtoTransferList *release_RAB_ContextFailedtoTransferList();
    void set_RAB_ContextFailedtoTransferList(RAB_ContextFailedtoTransferList *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq101   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SRNS_ContextResponseIEs_Value value;

    __seq101();
    __seq101(const __seq101 &);
    __seq101(id, criticality, const value &);

    __seq101 & operator = (const __seq101 &);
    int operator == (const __seq101 &) const;
    int operator != (const __seq101 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared28   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OSS_UINT32 dl_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 ul_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 dl_N_PDU_SequenceNumber;
    typedef OSS_UINT32 ul_N_PDU_SequenceNumber;
    typedef __shared4 iE_Extensions;

    __shared28();
    __shared28(const __shared28 &);
    __shared28(const rAB_ID &, dl_GTP_PDU_SequenceNumber, ul_GTP_PDU_SequenceNumber, 
	dl_N_PDU_SequenceNumber, ul_N_PDU_SequenceNumber, const iE_Extensions &);
    __shared28(const rAB_ID &);

    __shared28 & operator = (const __shared28 &);
    int operator == (const __shared28 &) const;
    int operator != (const __shared28 &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    dl_GTP_PDU_SequenceNumber *get_dl_GTP_PDU_SequenceNumber();
    const dl_GTP_PDU_SequenceNumber *get_dl_GTP_PDU_SequenceNumber() const;
    void set_dl_GTP_PDU_SequenceNumber(dl_GTP_PDU_SequenceNumber);
    int dl_GTP_PDU_SequenceNumber_is_present() const;
    void omit_dl_GTP_PDU_SequenceNumber();

    ul_GTP_PDU_SequenceNumber *get_ul_GTP_PDU_SequenceNumber();
    const ul_GTP_PDU_SequenceNumber *get_ul_GTP_PDU_SequenceNumber() const;
    void set_ul_GTP_PDU_SequenceNumber(ul_GTP_PDU_SequenceNumber);
    int ul_GTP_PDU_SequenceNumber_is_present() const;
    void omit_ul_GTP_PDU_SequenceNumber();

    dl_N_PDU_SequenceNumber *get_dl_N_PDU_SequenceNumber();
    const dl_N_PDU_SequenceNumber *get_dl_N_PDU_SequenceNumber() const;
    void set_dl_N_PDU_SequenceNumber(dl_N_PDU_SequenceNumber);
    int dl_N_PDU_SequenceNumber_is_present() const;
    void omit_dl_N_PDU_SequenceNumber();

    ul_N_PDU_SequenceNumber *get_ul_N_PDU_SequenceNumber();
    const ul_N_PDU_SequenceNumber *get_ul_N_PDU_SequenceNumber() const;
    void set_ul_N_PDU_SequenceNumber(ul_N_PDU_SequenceNumber);
    int ul_N_PDU_SequenceNumber_is_present() const;
    void omit_ul_N_PDU_SequenceNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    dl_GTP_PDU_SequenceNumber dl_GTP_PDU_SequenceNumber_field;
    ul_GTP_PDU_SequenceNumber ul_GTP_PDU_SequenceNumber_field;
    dl_N_PDU_SequenceNumber dl_N_PDU_SequenceNumber_field;
    ul_N_PDU_SequenceNumber ul_N_PDU_SequenceNumber_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared28 RAB_ContextItem;

class OSS_PUBLIC RAB_ContextItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ContextItemIEs_Value();
    RAB_ContextItemIEs_Value(const RAB_ContextItemIEs_Value &);
    ~RAB_ContextItemIEs_Value();
    RAB_ContextItemIEs_Value & operator = (const RAB_ContextItemIEs_Value &);
    int operator == (const RAB_ContextItemIEs_Value &) const;
    int operator != (const RAB_ContextItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared28 *get_RAB_ContextItem();
    const __shared28 *get_RAB_ContextItem() const;
    void set_RAB_ContextItem(const __shared28 &);
    __shared28 *release_RAB_ContextItem();
    void set_RAB_ContextItem(__shared28 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq103;

class OSS_PUBLIC __seqof95 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq103 component;

    __seqof95();
    __seqof95(const __seqof95 &);
    ~__seqof95();

    __seqof95 & operator = (const __seqof95 &);
    int operator == (const __seqof95 &) const;
    int operator != (const __seqof95 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof95 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof95 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof95 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq103   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ContextItemIEs_Value value;

    __seq103();
    __seq103(const __seq103 &);
    __seq103(id, criticality, const value &);

    __seq103 & operator = (const __seq103 &);
    int operator == (const __seq103 &) const;
    int operator != (const __seq103 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef __shared20 RABs_ContextFailedtoTransferItem;

class OSS_PUBLIC RABs_ContextFailedtoTransferItemIEs_Value : public OssConstrainedOpenType
{
public:
    RABs_ContextFailedtoTransferItemIEs_Value();
    RABs_ContextFailedtoTransferItemIEs_Value(const RABs_ContextFailedtoTransferItemIEs_Value &);
    ~RABs_ContextFailedtoTransferItemIEs_Value();
    RABs_ContextFailedtoTransferItemIEs_Value & operator = (const RABs_ContextFailedtoTransferItemIEs_Value &);
    int operator == (const RABs_ContextFailedtoTransferItemIEs_Value &) const;
    int operator != (const RABs_ContextFailedtoTransferItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared20 *get_RABs_ContextFailedtoTransferItem();
    const __shared20 *get_RABs_ContextFailedtoTransferItem() const;
    void set_RABs_ContextFailedtoTransferItem(const __shared20 &);
    __shared20 *release_RABs_ContextFailedtoTransferItem();
    void set_RABs_ContextFailedtoTransferItem(__shared20 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq105;

class OSS_PUBLIC __seqof97 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq105 component;

    __seqof97();
    __seqof97(const __seqof97 &);
    ~__seqof97();

    __seqof97 & operator = (const __seqof97 &);
    int operator == (const __seqof97 &) const;
    int operator != (const __seqof97 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof97 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof97 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof97 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq105   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RABs_ContextFailedtoTransferItemIEs_Value value;

    __seq105();
    __seq105(const __seq105 &);
    __seq105(id, criticality, const value &);

    __seq105 & operator = (const __seq105 &);
    int operator == (const __seq105 &) const;
    int operator != (const __seq105 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC SecurityModeCommandIEs_Value : public OssConstrainedOpenType
{
public:
    SecurityModeCommandIEs_Value();
    SecurityModeCommandIEs_Value(const SecurityModeCommandIEs_Value &);
    ~SecurityModeCommandIEs_Value();
    SecurityModeCommandIEs_Value & operator = (const SecurityModeCommandIEs_Value &);
    int operator == (const SecurityModeCommandIEs_Value &) const;
    int operator != (const SecurityModeCommandIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared15 *get_IntegrityProtectionInformation();
    const __shared15 *get_IntegrityProtectionInformation() const;
    void set_IntegrityProtectionInformation(const __shared15 &);
    __shared15 *release_IntegrityProtectionInformation();
    void set_IntegrityProtectionInformation(__shared15 *);

    __shared15 *get_EncryptionInformation();
    const __shared15 *get_EncryptionInformation() const;
    void set_EncryptionInformation(const __shared15 &);
    __shared15 *release_EncryptionInformation();
    void set_EncryptionInformation(__shared15 *);

    KeyStatus *get_KeyStatus();
    const KeyStatus *get_KeyStatus() const;
    void set_KeyStatus(const KeyStatus &);
    KeyStatus *release_KeyStatus();
    void set_KeyStatus(KeyStatus *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq107   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SecurityModeCommandIEs_Value value;

    __seq107();
    __seq107(const __seq107 &);
    __seq107(id, criticality, const value &);

    __seq107 & operator = (const __seq107 &);
    int operator == (const __seq107 &) const;
    int operator != (const __seq107 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC SecurityModeCompleteIEs_Value : public OssConstrainedOpenType
{
public:
    SecurityModeCompleteIEs_Value();
    SecurityModeCompleteIEs_Value(const SecurityModeCompleteIEs_Value &);
    ~SecurityModeCompleteIEs_Value();
    SecurityModeCompleteIEs_Value & operator = (const SecurityModeCompleteIEs_Value &);
    int operator == (const SecurityModeCompleteIEs_Value &) const;
    int operator != (const SecurityModeCompleteIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    ChosenIntegrityProtectionAlgorithm *get_ChosenIntegrityProtectionAlgorithm();
    const ChosenIntegrityProtectionAlgorithm *get_ChosenIntegrityProtectionAlgorithm() const;
    void set_ChosenIntegrityProtectionAlgorithm(const ChosenIntegrityProtectionAlgorithm &);
    ChosenIntegrityProtectionAlgorithm *release_ChosenIntegrityProtectionAlgorithm();
    void set_ChosenIntegrityProtectionAlgorithm(ChosenIntegrityProtectionAlgorithm *);

    ChosenEncryptionAlgorithm *get_ChosenEncryptionAlgorithm();
    const ChosenEncryptionAlgorithm *get_ChosenEncryptionAlgorithm() const;
    void set_ChosenEncryptionAlgorithm(const ChosenEncryptionAlgorithm &);
    ChosenEncryptionAlgorithm *release_ChosenEncryptionAlgorithm();
    void set_ChosenEncryptionAlgorithm(ChosenEncryptionAlgorithm *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq109   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SecurityModeCompleteIEs_Value value;

    __seq109();
    __seq109(const __seq109 &);
    __seq109(id, criticality, const value &);

    __seq109 & operator = (const __seq109 &);
    int operator == (const __seq109 &) const;
    int operator != (const __seq109 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof107;

class OSS_PUBLIC RAB_DataVolumeReportRequestList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof107 component;

    RAB_DataVolumeReportRequestList();
    RAB_DataVolumeReportRequestList(const RAB_DataVolumeReportRequestList &);
    ~RAB_DataVolumeReportRequestList();

    RAB_DataVolumeReportRequestList & operator = (const RAB_DataVolumeReportRequestList &);
    int operator == (const RAB_DataVolumeReportRequestList &) const;
    int operator != (const RAB_DataVolumeReportRequestList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_DataVolumeReportRequestList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_DataVolumeReportRequestList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_DataVolumeReportRequestList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DataVolumeReportRequestIEs_Value : public OssConstrainedOpenType
{
public:
    DataVolumeReportRequestIEs_Value();
    DataVolumeReportRequestIEs_Value(const DataVolumeReportRequestIEs_Value &);
    ~DataVolumeReportRequestIEs_Value();
    DataVolumeReportRequestIEs_Value & operator = (const DataVolumeReportRequestIEs_Value &);
    int operator == (const DataVolumeReportRequestIEs_Value &) const;
    int operator != (const DataVolumeReportRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataVolumeReportRequestList *get_RAB_DataVolumeReportRequestList();
    const RAB_DataVolumeReportRequestList *get_RAB_DataVolumeReportRequestList() const;
    void set_RAB_DataVolumeReportRequestList(const RAB_DataVolumeReportRequestList &);
    RAB_DataVolumeReportRequestList *release_RAB_DataVolumeReportRequestList();
    void set_RAB_DataVolumeReportRequestList(RAB_DataVolumeReportRequestList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq113   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef DataVolumeReportRequestIEs_Value value;

    __seq113();
    __seq113(const __seq113 &);
    __seq113(id, criticality, const value &);

    __seq113 & operator = (const __seq113 &);
    int operator == (const __seq113 &) const;
    int operator != (const __seq113 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef __shared16 RAB_DataVolumeReportRequestItem;

class OSS_PUBLIC RAB_DataVolumeReportRequestItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_DataVolumeReportRequestItemIEs_Value();
    RAB_DataVolumeReportRequestItemIEs_Value(const RAB_DataVolumeReportRequestItemIEs_Value &);
    ~RAB_DataVolumeReportRequestItemIEs_Value();
    RAB_DataVolumeReportRequestItemIEs_Value & operator = (const RAB_DataVolumeReportRequestItemIEs_Value &);
    int operator == (const RAB_DataVolumeReportRequestItemIEs_Value &) const;
    int operator != (const RAB_DataVolumeReportRequestItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared16 *get_RAB_DataVolumeReportRequestItem();
    const __shared16 *get_RAB_DataVolumeReportRequestItem() const;
    void set_RAB_DataVolumeReportRequestItem(const __shared16 &);
    __shared16 *release_RAB_DataVolumeReportRequestItem();
    void set_RAB_DataVolumeReportRequestItem(__shared16 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq115;

class OSS_PUBLIC __seqof107 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq115 component;

    __seqof107();
    __seqof107(const __seqof107 &);
    ~__seqof107();

    __seqof107 & operator = (const __seqof107 &);
    int operator == (const __seqof107 &) const;
    int operator != (const __seqof107 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof107 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof107 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof107 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq115   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_DataVolumeReportRequestItemIEs_Value value;

    __seq115();
    __seq115(const __seq115 &);
    __seq115(id, criticality, const value &);

    __seq115 & operator = (const __seq115 &);
    int operator == (const __seq115 &) const;
    int operator != (const __seq115 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof111;

class OSS_PUBLIC RAB_FailedtoReportList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof111 component;

    RAB_FailedtoReportList();
    RAB_FailedtoReportList(const RAB_FailedtoReportList &);
    ~RAB_FailedtoReportList();

    RAB_FailedtoReportList & operator = (const RAB_FailedtoReportList &);
    int operator == (const RAB_FailedtoReportList &) const;
    int operator != (const RAB_FailedtoReportList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_FailedtoReportList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_FailedtoReportList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_FailedtoReportList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DataVolumeReportIEs_Value : public OssConstrainedOpenType
{
public:
    DataVolumeReportIEs_Value();
    DataVolumeReportIEs_Value(const DataVolumeReportIEs_Value &);
    ~DataVolumeReportIEs_Value();
    DataVolumeReportIEs_Value & operator = (const DataVolumeReportIEs_Value &);
    int operator == (const DataVolumeReportIEs_Value &) const;
    int operator != (const DataVolumeReportIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataVolumeReportList *get_RAB_DataVolumeReportList();
    const RAB_DataVolumeReportList *get_RAB_DataVolumeReportList() const;
    void set_RAB_DataVolumeReportList(const RAB_DataVolumeReportList &);
    RAB_DataVolumeReportList *release_RAB_DataVolumeReportList();
    void set_RAB_DataVolumeReportList(RAB_DataVolumeReportList *);

    RAB_FailedtoReportList *get_RAB_FailedtoReportList();
    const RAB_FailedtoReportList *get_RAB_FailedtoReportList() const;
    void set_RAB_FailedtoReportList(const RAB_FailedtoReportList &);
    RAB_FailedtoReportList *release_RAB_FailedtoReportList();
    void set_RAB_FailedtoReportList(RAB_FailedtoReportList *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq117   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef DataVolumeReportIEs_Value value;

    __seq117();
    __seq117(const __seq117 &);
    __seq117(id, criticality, const value &);

    __seq117 & operator = (const __seq117 &);
    int operator == (const __seq117 &) const;
    int operator != (const __seq117 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef __shared20 RABs_failed_to_reportItem;

class OSS_PUBLIC RABs_failed_to_reportItemIEs_Value : public OssConstrainedOpenType
{
public:
    RABs_failed_to_reportItemIEs_Value();
    RABs_failed_to_reportItemIEs_Value(const RABs_failed_to_reportItemIEs_Value &);
    ~RABs_failed_to_reportItemIEs_Value();
    RABs_failed_to_reportItemIEs_Value & operator = (const RABs_failed_to_reportItemIEs_Value &);
    int operator == (const RABs_failed_to_reportItemIEs_Value &) const;
    int operator != (const RABs_failed_to_reportItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared20 *get_RABs_failed_to_reportItem();
    const __shared20 *get_RABs_failed_to_reportItem() const;
    void set_RABs_failed_to_reportItem(const __shared20 &);
    __shared20 *release_RABs_failed_to_reportItem();
    void set_RABs_failed_to_reportItem(__shared20 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq119;

class OSS_PUBLIC __seqof111 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq119 component;

    __seqof111();
    __seqof111(const __seqof111 &);
    ~__seqof111();

    __seqof111 & operator = (const __seqof111 &);
    int operator == (const __seqof111 &) const;
    int operator != (const __seqof111 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof111 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof111 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof111 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq119   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RABs_failed_to_reportItemIEs_Value value;

    __seq119();
    __seq119(const __seq119 &);
    __seq119(id, criticality, const value &);

    __seq119 & operator = (const __seq119 &);
    int operator == (const __seq119 &) const;
    int operator != (const __seq119 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC ResetIEs_Value : public OssConstrainedOpenType
{
public:
    ResetIEs_Value();
    ResetIEs_Value(const ResetIEs_Value &);
    ~ResetIEs_Value();
    ResetIEs_Value & operator = (const ResetIEs_Value &);
    int operator == (const ResetIEs_Value &) const;
    int operator != (const ResetIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC ResetExtensions_Extension : public OssConstrainedOpenType
{
public:
    ResetExtensions_Extension();
    ResetExtensions_Extension(const ResetExtensions_Extension &);
    ~ResetExtensions_Extension();
    ResetExtensions_Extension & operator = (const ResetExtensions_Extension &);
    int operator == (const ResetExtensions_Extension &) const;
    int operator != (const ResetExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq121   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetIEs_Value value;

    __seq121();
    __seq121(const __seq121 &);
    __seq121(id, criticality, const value &);

    __seq121 & operator = (const __seq121 &);
    int operator == (const __seq121 &) const;
    int operator != (const __seq121 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared17   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetExtensions_Extension extensionValue;

    __shared17();
    __shared17(const __shared17 &);
    __shared17(id, criticality, const extensionValue &);

    __shared17 & operator = (const __shared17 &);
    int operator == (const __shared17 &) const;
    int operator != (const __shared17 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC ResetAcknowledgeIEs_Value : public OssConstrainedOpenType
{
public:
    ResetAcknowledgeIEs_Value();
    ResetAcknowledgeIEs_Value(const ResetAcknowledgeIEs_Value &);
    ~ResetAcknowledgeIEs_Value();
    ResetAcknowledgeIEs_Value & operator = (const ResetAcknowledgeIEs_Value &);
    int operator == (const ResetAcknowledgeIEs_Value &) const;
    int operator != (const ResetAcknowledgeIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq123   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetAcknowledgeIEs_Value value;

    __seq123();
    __seq123(const __seq123 &);
    __seq123(id, criticality, const value &);

    __seq123 & operator = (const __seq123 &);
    int operator == (const __seq123 &) const;
    int operator != (const __seq123 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof119;

class OSS_PUBLIC ResetResourceList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof119 component;

    ResetResourceList();
    ResetResourceList(const ResetResourceList &);
    ~ResetResourceList();

    ResetResourceList & operator = (const ResetResourceList &);
    int operator == (const ResetResourceList &) const;
    int operator != (const ResetResourceList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(ResetResourceList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, ResetResourceList *);

    int remove_front();
    int remove_after(OssIndex);

    ResetResourceList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ResetResourceIEs_Value : public OssConstrainedOpenType
{
public:
    ResetResourceIEs_Value();
    ResetResourceIEs_Value(const ResetResourceIEs_Value &);
    ~ResetResourceIEs_Value();
    ResetResourceIEs_Value & operator = (const ResetResourceIEs_Value &);
    int operator == (const ResetResourceIEs_Value &) const;
    int operator != (const ResetResourceIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    ResetResourceList *get_ResetResourceList();
    const ResetResourceList *get_ResetResourceList() const;
    void set_ResetResourceList(const ResetResourceList &);
    ResetResourceList *release_ResetResourceList();
    void set_ResetResourceList(ResetResourceList *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq125   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetResourceIEs_Value value;

    __seq125();
    __seq125(const __seq125 &);
    __seq125(id, criticality, const value &);

    __seq125 & operator = (const __seq125 &);
    int operator == (const __seq125 &) const;
    int operator != (const __seq125 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared19   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString iuSigConId;
    typedef __shared4 iE_Extensions;

    __shared19();
    __shared19(const __shared19 &);
    __shared19(const iuSigConId &, const iE_Extensions &);
    __shared19(const iuSigConId &);

    __shared19 & operator = (const __shared19 &);
    int operator == (const __shared19 &) const;
    int operator != (const __shared19 &) const;

    iuSigConId & get_iuSigConId();
    const iuSigConId & get_iuSigConId() const;
    void set_iuSigConId(const iuSigConId &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    iuSigConId iuSigConId_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared19 ResetResourceItem;

class OSS_PUBLIC ResetResourceItemIEs_Value : public OssConstrainedOpenType
{
public:
    ResetResourceItemIEs_Value();
    ResetResourceItemIEs_Value(const ResetResourceItemIEs_Value &);
    ~ResetResourceItemIEs_Value();
    ResetResourceItemIEs_Value & operator = (const ResetResourceItemIEs_Value &);
    int operator == (const ResetResourceItemIEs_Value &) const;
    int operator != (const ResetResourceItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared19 *get_ResetResourceItem();
    const __shared19 *get_ResetResourceItem() const;
    void set_ResetResourceItem(const __shared19 &);
    __shared19 *release_ResetResourceItem();
    void set_ResetResourceItem(__shared19 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq127;

class OSS_PUBLIC __seqof119 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq127 component;

    __seqof119();
    __seqof119(const __seqof119 &);
    ~__seqof119();

    __seqof119 & operator = (const __seqof119 &);
    int operator == (const __seqof119 &) const;
    int operator != (const __seqof119 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof119 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof119 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof119 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq127   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetResourceItemIEs_Value value;

    __seq127();
    __seq127(const __seq127 &);
    __seq127(id, criticality, const value &);

    __seq127 & operator = (const __seq127 &);
    int operator == (const __seq127 &) const;
    int operator != (const __seq127 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof123;

class OSS_PUBLIC ResetResourceAckList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof123 component;

    ResetResourceAckList();
    ResetResourceAckList(const ResetResourceAckList &);
    ~ResetResourceAckList();

    ResetResourceAckList & operator = (const ResetResourceAckList &);
    int operator == (const ResetResourceAckList &) const;
    int operator != (const ResetResourceAckList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(ResetResourceAckList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, ResetResourceAckList *);

    int remove_front();
    int remove_after(OssIndex);

    ResetResourceAckList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC ResetResourceAcknowledgeIEs_Value : public OssConstrainedOpenType
{
public:
    ResetResourceAcknowledgeIEs_Value();
    ResetResourceAcknowledgeIEs_Value(const ResetResourceAcknowledgeIEs_Value &);
    ~ResetResourceAcknowledgeIEs_Value();
    ResetResourceAcknowledgeIEs_Value & operator = (const ResetResourceAcknowledgeIEs_Value &);
    int operator == (const ResetResourceAcknowledgeIEs_Value &) const;
    int operator != (const ResetResourceAcknowledgeIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    ResetResourceAckList *get_ResetResourceAckList();
    const ResetResourceAckList *get_ResetResourceAckList() const;
    void set_ResetResourceAckList(const ResetResourceAckList &);
    ResetResourceAckList *release_ResetResourceAckList();
    void set_ResetResourceAckList(ResetResourceAckList *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq129   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetResourceAcknowledgeIEs_Value value;

    __seq129();
    __seq129(const __seq129 &);
    __seq129(id, criticality, const value &);

    __seq129 & operator = (const __seq129 &);
    int operator == (const __seq129 &) const;
    int operator != (const __seq129 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef __shared19 ResetResourceAckItem;

class OSS_PUBLIC ResetResourceAckItemIEs_Value : public OssConstrainedOpenType
{
public:
    ResetResourceAckItemIEs_Value();
    ResetResourceAckItemIEs_Value(const ResetResourceAckItemIEs_Value &);
    ~ResetResourceAckItemIEs_Value();
    ResetResourceAckItemIEs_Value & operator = (const ResetResourceAckItemIEs_Value &);
    int operator == (const ResetResourceAckItemIEs_Value &) const;
    int operator != (const ResetResourceAckItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared19 *get_ResetResourceAckItem();
    const __shared19 *get_ResetResourceAckItem() const;
    void set_ResetResourceAckItem(const __shared19 &);
    __shared19 *release_ResetResourceAckItem();
    void set_ResetResourceAckItem(__shared19 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq131;

class OSS_PUBLIC __seqof123 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq131 component;

    __seqof123();
    __seqof123(const __seqof123 &);
    ~__seqof123();

    __seqof123 & operator = (const __seqof123 &);
    int operator == (const __seqof123 &) const;
    int operator != (const __seqof123 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof123 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof123 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof123 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq131   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ResetResourceAckItemIEs_Value value;

    __seq131();
    __seq131(const __seq131 &);
    __seq131(id, criticality, const value &);

    __seq131 & operator = (const __seq131 &);
    int operator == (const __seq131 &) const;
    int operator != (const __seq131 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof127;

class OSS_PUBLIC RAB_ReleaseList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof127 component;

    RAB_ReleaseList();
    RAB_ReleaseList(const RAB_ReleaseList &);
    ~RAB_ReleaseList();

    RAB_ReleaseList & operator = (const RAB_ReleaseList &);
    int operator == (const RAB_ReleaseList &) const;
    int operator != (const RAB_ReleaseList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ReleaseList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ReleaseList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ReleaseList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_ReleaseRequestIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ReleaseRequestIEs_Value();
    RAB_ReleaseRequestIEs_Value(const RAB_ReleaseRequestIEs_Value &);
    ~RAB_ReleaseRequestIEs_Value();
    RAB_ReleaseRequestIEs_Value & operator = (const RAB_ReleaseRequestIEs_Value &);
    int operator == (const RAB_ReleaseRequestIEs_Value &) const;
    int operator != (const RAB_ReleaseRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ReleaseList *get_RAB_ReleaseList();
    const RAB_ReleaseList *get_RAB_ReleaseList() const;
    void set_RAB_ReleaseList(const RAB_ReleaseList &);
    RAB_ReleaseList *release_RAB_ReleaseList();
    void set_RAB_ReleaseList(RAB_ReleaseList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq133   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ReleaseRequestIEs_Value value;

    __seq133();
    __seq133(const __seq133 &);
    __seq133(id, criticality, const value &);

    __seq133 & operator = (const __seq133 &);
    int operator == (const __seq133 &) const;
    int operator != (const __seq133 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_ReleaseItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ReleaseItemIEs_Value();
    RAB_ReleaseItemIEs_Value(const RAB_ReleaseItemIEs_Value &);
    ~RAB_ReleaseItemIEs_Value();
    RAB_ReleaseItemIEs_Value & operator = (const RAB_ReleaseItemIEs_Value &);
    int operator == (const RAB_ReleaseItemIEs_Value &) const;
    int operator != (const RAB_ReleaseItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared20 *get_RAB_ReleaseItem();
    const __shared20 *get_RAB_ReleaseItem() const;
    void set_RAB_ReleaseItem(const __shared20 &);
    __shared20 *release_RAB_ReleaseItem();
    void set_RAB_ReleaseItem(__shared20 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq135;

class OSS_PUBLIC __seqof127 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq135 component;

    __seqof127();
    __seqof127(const __seqof127 &);
    ~__seqof127();

    __seqof127 & operator = (const __seqof127 &);
    int operator == (const __seqof127 &) const;
    int operator != (const __seqof127 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof127 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof127 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof127 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq135   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ReleaseItemIEs_Value value;

    __seq135();
    __seq135(const __seq135 &);
    __seq135(id, criticality, const value &);

    __seq135 & operator = (const __seq135 &);
    int operator == (const __seq135 &) const;
    int operator != (const __seq135 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared21   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef PrivateMessage_IEs_Value value;

    __shared21();
    __shared21(const __shared21 &);
    __shared21(id, criticality, const value &);

    __shared21 & operator = (const __shared21 &);
    int operator == (const __shared21 &) const;
    int operator != (const __shared21 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC PagingIEs_Value : public OssConstrainedOpenType
{
public:
    PagingIEs_Value();
    PagingIEs_Value(const PagingIEs_Value &);
    ~PagingIEs_Value();
    PagingIEs_Value & operator = (const PagingIEs_Value &);
    int operator == (const PagingIEs_Value &) const;
    int operator != (const PagingIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    PermanentNAS_UE_ID *get_PermanentNAS_UE_ID();
    const PermanentNAS_UE_ID *get_PermanentNAS_UE_ID() const;
    void set_PermanentNAS_UE_ID(const PermanentNAS_UE_ID &);
    PermanentNAS_UE_ID *release_PermanentNAS_UE_ID();
    void set_PermanentNAS_UE_ID(PermanentNAS_UE_ID *);

    TemporaryUE_ID *get_TemporaryUE_ID();
    const TemporaryUE_ID *get_TemporaryUE_ID() const;
    void set_TemporaryUE_ID(const TemporaryUE_ID &);
    TemporaryUE_ID *release_TemporaryUE_ID();
    void set_TemporaryUE_ID(TemporaryUE_ID *);

    PagingAreaID *get_PagingAreaID();
    const PagingAreaID *get_PagingAreaID() const;
    void set_PagingAreaID(const PagingAreaID &);
    PagingAreaID *release_PagingAreaID();
    void set_PagingAreaID(PagingAreaID *);

    PagingCause *get_PagingCause();
    const PagingCause *get_PagingCause() const;
    void set_PagingCause(const PagingCause &);
    PagingCause *release_PagingCause();
    void set_PagingCause(PagingCause *);

    NonSearchingIndication *get_NonSearchingIndication();
    const NonSearchingIndication *get_NonSearchingIndication() const;
    void set_NonSearchingIndication(const NonSearchingIndication &);
    NonSearchingIndication *release_NonSearchingIndication();
    void set_NonSearchingIndication(NonSearchingIndication *);

    DRX_CycleLengthCoefficient *get_DRX_CycleLengthCoefficient();
    const DRX_CycleLengthCoefficient *get_DRX_CycleLengthCoefficient() const;
    void set_DRX_CycleLengthCoefficient(const DRX_CycleLengthCoefficient &);
    DRX_CycleLengthCoefficient *release_DRX_CycleLengthCoefficient();
    void set_DRX_CycleLengthCoefficient(DRX_CycleLengthCoefficient *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq143   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef PagingIEs_Value value;

    __seq143();
    __seq143(const __seq143 &);
    __seq143(id, criticality, const value &);

    __seq143 & operator = (const __seq143 &);
    int operator == (const __seq143 &) const;
    int operator != (const __seq143 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC CommonID_IEs_Value : public OssConstrainedOpenType
{
public:
    CommonID_IEs_Value();
    CommonID_IEs_Value(const CommonID_IEs_Value &);
    ~CommonID_IEs_Value();
    CommonID_IEs_Value & operator = (const CommonID_IEs_Value &);
    int operator == (const CommonID_IEs_Value &) const;
    int operator != (const CommonID_IEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    PermanentNAS_UE_ID *get_PermanentNAS_UE_ID();
    const PermanentNAS_UE_ID *get_PermanentNAS_UE_ID() const;
    void set_PermanentNAS_UE_ID(const PermanentNAS_UE_ID &);
    PermanentNAS_UE_ID *release_PermanentNAS_UE_ID();
    void set_PermanentNAS_UE_ID(PermanentNAS_UE_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC CommonIDExtensions_Extension : public OssConstrainedOpenType
{
public:
    CommonIDExtensions_Extension();
    CommonIDExtensions_Extension(const CommonIDExtensions_Extension &);
    ~CommonIDExtensions_Extension();
    CommonIDExtensions_Extension & operator = (const CommonIDExtensions_Extension &);
    int operator == (const CommonIDExtensions_Extension &) const;
    int operator != (const CommonIDExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    SNA_Access_Information *get_SNA_Access_Information();
    const SNA_Access_Information *get_SNA_Access_Information() const;
    void set_SNA_Access_Information(const SNA_Access_Information &);
    SNA_Access_Information *release_SNA_Access_Information();
    void set_SNA_Access_Information(SNA_Access_Information *);

    UESBI_Iu *get_UESBI_Iu();
    const UESBI_Iu *get_UESBI_Iu() const;
    void set_UESBI_Iu(const UESBI_Iu &);
    UESBI_Iu *release_UESBI_Iu();
    void set_UESBI_Iu(UESBI_Iu *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq145   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CommonID_IEs_Value value;

    __seq145();
    __seq145(const __seq145 &);
    __seq145(id, criticality, const value &);

    __seq145 & operator = (const __seq145 &);
    int operator == (const __seq145 &) const;
    int operator != (const __seq145 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq146   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CommonIDExtensions_Extension extensionValue;

    __seq146();
    __seq146(const __seq146 &);
    __seq146(id, criticality, const extensionValue &);

    __seq146 & operator = (const __seq146 &);
    int operator == (const __seq146 &) const;
    int operator != (const __seq146 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC CN_InvokeTraceIEs_Value : public OssConstrainedOpenType
{
public:
    CN_InvokeTraceIEs_Value();
    CN_InvokeTraceIEs_Value(const CN_InvokeTraceIEs_Value &);
    ~CN_InvokeTraceIEs_Value();
    CN_InvokeTraceIEs_Value & operator = (const CN_InvokeTraceIEs_Value &);
    int operator == (const CN_InvokeTraceIEs_Value &) const;
    int operator != (const CN_InvokeTraceIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TraceType *get_TraceType();
    const TraceType *get_TraceType() const;
    void set_TraceType(const TraceType &);
    TraceType *release_TraceType();
    void set_TraceType(TraceType *);

    TraceReference *get_TraceReference();
    const TraceReference *get_TraceReference() const;
    void set_TraceReference(const TraceReference &);
    TraceReference *release_TraceReference();
    void set_TraceReference(TraceReference *);

    TriggerID *get_TriggerID();
    const TriggerID *get_TriggerID() const;
    void set_TriggerID(const TriggerID &);
    TriggerID *release_TriggerID();
    void set_TriggerID(TriggerID *);

    UE_ID *get_UE_ID();
    const UE_ID *get_UE_ID() const;
    void set_UE_ID(const UE_ID &);
    UE_ID *release_UE_ID();
    void set_UE_ID(UE_ID *);

    OMC_ID *get_OMC_ID();
    const OMC_ID *get_OMC_ID() const;
    void set_OMC_ID(const OMC_ID &);
    OMC_ID *release_OMC_ID();
    void set_OMC_ID(OMC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC CN_InvokeTraceExtensions_Extension : public OssConstrainedOpenType
{
public:
    CN_InvokeTraceExtensions_Extension();
    CN_InvokeTraceExtensions_Extension(const CN_InvokeTraceExtensions_Extension &);
    ~CN_InvokeTraceExtensions_Extension();
    CN_InvokeTraceExtensions_Extension & operator = (const CN_InvokeTraceExtensions_Extension &);
    int operator == (const CN_InvokeTraceExtensions_Extension &) const;
    int operator != (const CN_InvokeTraceExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TracePropagationParameters *get_TracePropagationParameters();
    const TracePropagationParameters *get_TracePropagationParameters() const;
    void set_TracePropagationParameters(const TracePropagationParameters &);
    TracePropagationParameters *release_TracePropagationParameters();
    void set_TracePropagationParameters(TracePropagationParameters *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq147   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CN_InvokeTraceIEs_Value value;

    __seq147();
    __seq147(const __seq147 &);
    __seq147(id, criticality, const value &);

    __seq147 & operator = (const __seq147 &);
    int operator == (const __seq147 &) const;
    int operator != (const __seq147 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq148   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CN_InvokeTraceExtensions_Extension extensionValue;

    __seq148();
    __seq148(const __seq148 &);
    __seq148(id, criticality, const extensionValue &);

    __seq148 & operator = (const __seq148 &);
    int operator == (const __seq148 &) const;
    int operator != (const __seq148 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC CN_DeactivateTraceIEs_Value : public OssConstrainedOpenType
{
public:
    CN_DeactivateTraceIEs_Value();
    CN_DeactivateTraceIEs_Value(const CN_DeactivateTraceIEs_Value &);
    ~CN_DeactivateTraceIEs_Value();
    CN_DeactivateTraceIEs_Value & operator = (const CN_DeactivateTraceIEs_Value &);
    int operator == (const CN_DeactivateTraceIEs_Value &) const;
    int operator != (const CN_DeactivateTraceIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    TraceReference *get_TraceReference();
    const TraceReference *get_TraceReference() const;
    void set_TraceReference(const TraceReference &);
    TraceReference *release_TraceReference();
    void set_TraceReference(TraceReference *);

    TriggerID *get_TriggerID();
    const TriggerID *get_TriggerID() const;
    void set_TriggerID(const TriggerID &);
    TriggerID *release_TriggerID();
    void set_TriggerID(TriggerID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq149   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef CN_DeactivateTraceIEs_Value value;

    __seq149();
    __seq149(const __seq149 &);
    __seq149(id, criticality, const value &);

    __seq149 & operator = (const __seq149 &);
    int operator == (const __seq149 &) const;
    int operator != (const __seq149 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC LocationReportingControlIEs_Value : public OssConstrainedOpenType
{
public:
    LocationReportingControlIEs_Value();
    LocationReportingControlIEs_Value(const LocationReportingControlIEs_Value &);
    ~LocationReportingControlIEs_Value();
    LocationReportingControlIEs_Value & operator = (const LocationReportingControlIEs_Value &);
    int operator == (const LocationReportingControlIEs_Value &) const;
    int operator != (const LocationReportingControlIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RequestType *get_RequestType();
    const RequestType *get_RequestType() const;
    void set_RequestType(const RequestType &);
    RequestType *release_RequestType();
    void set_RequestType(RequestType *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC LocationReportingControlExtensions_Extension : public OssConstrainedOpenType
{
public:
    LocationReportingControlExtensions_Extension();
    LocationReportingControlExtensions_Extension(const LocationReportingControlExtensions_Extension &);
    ~LocationReportingControlExtensions_Extension();
    LocationReportingControlExtensions_Extension & operator = (const LocationReportingControlExtensions_Extension &);
    int operator == (const LocationReportingControlExtensions_Extension &) const;
    int operator != (const LocationReportingControlExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    VerticalAccuracyCode *get_VerticalAccuracyCode();
    const VerticalAccuracyCode *get_VerticalAccuracyCode() const;
    void set_VerticalAccuracyCode(const VerticalAccuracyCode &);
    VerticalAccuracyCode *release_VerticalAccuracyCode();
    void set_VerticalAccuracyCode(VerticalAccuracyCode *);

    ResponseTime *get_ResponseTime();
    const ResponseTime *get_ResponseTime() const;
    void set_ResponseTime(const ResponseTime &);
    ResponseTime *release_ResponseTime();
    void set_ResponseTime(ResponseTime *);

    PositioningPriority *get_PositioningPriority();
    const PositioningPriority *get_PositioningPriority() const;
    void set_PositioningPriority(const PositioningPriority &);
    PositioningPriority *release_PositioningPriority();
    void set_PositioningPriority(PositioningPriority *);

    ClientType *get_ClientType();
    const ClientType *get_ClientType() const;
    void set_ClientType(const ClientType &);
    ClientType *release_ClientType();
    void set_ClientType(ClientType *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq151   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationReportingControlIEs_Value value;

    __seq151();
    __seq151(const __seq151 &);
    __seq151(id, criticality, const value &);

    __seq151 & operator = (const __seq151 &);
    int operator == (const __seq151 &) const;
    int operator != (const __seq151 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq152   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationReportingControlExtensions_Extension extensionValue;

    __seq152();
    __seq152(const __seq152 &);
    __seq152(id, criticality, const extensionValue &);

    __seq152 & operator = (const __seq152 &);
    int operator == (const __seq152 &) const;
    int operator != (const __seq152 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC LocationReportIEs_Value : public OssConstrainedOpenType
{
public:
    LocationReportIEs_Value();
    LocationReportIEs_Value(const LocationReportIEs_Value &);
    ~LocationReportIEs_Value();
    LocationReportIEs_Value & operator = (const LocationReportIEs_Value &);
    int operator == (const LocationReportIEs_Value &) const;
    int operator != (const LocationReportIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    AreaIdentity *get_AreaIdentity();
    const AreaIdentity *get_AreaIdentity() const;
    void set_AreaIdentity(const AreaIdentity &);
    AreaIdentity *release_AreaIdentity();
    void set_AreaIdentity(AreaIdentity *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    RequestType *get_RequestType();
    const RequestType *get_RequestType() const;
    void set_RequestType(const RequestType &);
    RequestType *release_RequestType();
    void set_RequestType(RequestType *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC LocationReportExtensions_Extension : public OssConstrainedOpenType
{
public:
    LocationReportExtensions_Extension();
    LocationReportExtensions_Extension(const LocationReportExtensions_Extension &);
    ~LocationReportExtensions_Extension();
    LocationReportExtensions_Extension & operator = (const LocationReportExtensions_Extension &);
    int operator == (const LocationReportExtensions_Extension &) const;
    int operator != (const LocationReportExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    LastKnownServiceArea *get_LastKnownServiceArea();
    const LastKnownServiceArea *get_LastKnownServiceArea() const;
    void set_LastKnownServiceArea(const LastKnownServiceArea &);
    LastKnownServiceArea *release_LastKnownServiceArea();
    void set_LastKnownServiceArea(LastKnownServiceArea *);

    PositionData *get_PositionData();
    const PositionData *get_PositionData() const;
    void set_PositionData(const PositionData &);
    PositionData *release_PositionData();
    void set_PositionData(PositionData *);

    PositionDataSpecificToGERANIuMode *get_PositionDataSpecificToGERANIuMode();
    const PositionDataSpecificToGERANIuMode *get_PositionDataSpecificToGERANIuMode() const;
    void set_PositionDataSpecificToGERANIuMode(const PositionDataSpecificToGERANIuMode &);
    PositionDataSpecificToGERANIuMode *release_PositionDataSpecificToGERANIuMode();
    void set_PositionDataSpecificToGERANIuMode(PositionDataSpecificToGERANIuMode *);

    AccuracyFulfilmentIndicator *get_AccuracyFulfilmentIndicator();
    const AccuracyFulfilmentIndicator *get_AccuracyFulfilmentIndicator() const;
    void set_AccuracyFulfilmentIndicator(const AccuracyFulfilmentIndicator &);
    AccuracyFulfilmentIndicator *release_AccuracyFulfilmentIndicator();
    void set_AccuracyFulfilmentIndicator(AccuracyFulfilmentIndicator *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq153   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationReportIEs_Value value;

    __seq153();
    __seq153(const __seq153 &);
    __seq153(id, criticality, const value &);

    __seq153 & operator = (const __seq153 &);
    int operator == (const __seq153 &) const;
    int operator != (const __seq153 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq154   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationReportExtensions_Extension extensionValue;

    __seq154();
    __seq154(const __seq154 &);
    __seq154(id, criticality, const extensionValue &);

    __seq154 & operator = (const __seq154 &);
    int operator == (const __seq154 &) const;
    int operator != (const __seq154 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC InitialUE_MessageIEs_Value : public OssConstrainedOpenType
{
public:
    InitialUE_MessageIEs_Value();
    InitialUE_MessageIEs_Value(const InitialUE_MessageIEs_Value &);
    ~InitialUE_MessageIEs_Value();
    InitialUE_MessageIEs_Value & operator = (const InitialUE_MessageIEs_Value &);
    int operator == (const InitialUE_MessageIEs_Value &) const;
    int operator != (const InitialUE_MessageIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    LAI *get_LAI();
    const LAI *get_LAI() const;
    void set_LAI(const LAI &);
    LAI *release_LAI();
    void set_LAI(LAI *);

    RAC *get_RAC();
    const RAC *get_RAC() const;
    void set_RAC(const RAC &);
    RAC *release_RAC();
    void set_RAC(RAC *);

    SAI *get_SAI();
    const SAI *get_SAI() const;
    void set_SAI(const SAI &);
    SAI *release_SAI();
    void set_SAI(SAI *);

    NAS_PDU *get_NAS_PDU();
    const NAS_PDU *get_NAS_PDU() const;
    void set_NAS_PDU(const NAS_PDU &);
    NAS_PDU *release_NAS_PDU();
    void set_NAS_PDU(NAS_PDU *);

    IuSignallingConnectionIdentifier *get_IuSignallingConnectionIdentifier();
    const IuSignallingConnectionIdentifier *get_IuSignallingConnectionIdentifier() const;
    void set_IuSignallingConnectionIdentifier(const IuSignallingConnectionIdentifier &);
    IuSignallingConnectionIdentifier *release_IuSignallingConnectionIdentifier();
    void set_IuSignallingConnectionIdentifier(IuSignallingConnectionIdentifier *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq155   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef InitialUE_MessageIEs_Value value;

    __seq155();
    __seq155(const __seq155 &);
    __seq155(id, criticality, const value &);

    __seq155 & operator = (const __seq155 &);
    int operator == (const __seq155 &) const;
    int operator != (const __seq155 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC DirectTransferIEs_Value : public OssConstrainedOpenType
{
public:
    DirectTransferIEs_Value();
    DirectTransferIEs_Value(const DirectTransferIEs_Value &);
    ~DirectTransferIEs_Value();
    DirectTransferIEs_Value & operator = (const DirectTransferIEs_Value &);
    int operator == (const DirectTransferIEs_Value &) const;
    int operator != (const DirectTransferIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    NAS_PDU *get_NAS_PDU();
    const NAS_PDU *get_NAS_PDU() const;
    void set_NAS_PDU(const NAS_PDU &);
    NAS_PDU *release_NAS_PDU();
    void set_NAS_PDU(NAS_PDU *);

    LAI *get_LAI();
    const LAI *get_LAI() const;
    void set_LAI(const LAI &);
    LAI *release_LAI();
    void set_LAI(LAI *);

    RAC *get_RAC();
    const RAC *get_RAC() const;
    void set_RAC(const RAC &);
    RAC *release_RAC();
    void set_RAC(RAC *);

    SAI *get_SAI();
    const SAI *get_SAI() const;
    void set_SAI(const SAI &);
    SAI *release_SAI();
    void set_SAI(SAI *);

    SAPI *get_SAPI();
    const SAPI *get_SAPI() const;
    void set_SAPI(const SAPI &);
    SAPI *release_SAPI();
    void set_SAPI(SAPI *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq157   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef DirectTransferIEs_Value value;

    __seq157();
    __seq157(const __seq157 &);
    __seq157(id, criticality, const value &);

    __seq157 & operator = (const __seq157 &);
    int operator == (const __seq157 &) const;
    int operator != (const __seq157 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC OverloadIEs_Value : public OssConstrainedOpenType
{
public:
    OverloadIEs_Value();
    OverloadIEs_Value(const OverloadIEs_Value &);
    ~OverloadIEs_Value();
    OverloadIEs_Value & operator = (const OverloadIEs_Value &);
    int operator == (const OverloadIEs_Value &) const;
    int operator != (const OverloadIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    NumberOfSteps *get_NumberOfSteps();
    const NumberOfSteps *get_NumberOfSteps() const;
    void set_NumberOfSteps(const NumberOfSteps &);
    NumberOfSteps *release_NumberOfSteps();
    void set_NumberOfSteps(NumberOfSteps *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC OverloadExtensions_Extension : public OssConstrainedOpenType
{
public:
    OverloadExtensions_Extension();
    OverloadExtensions_Extension(const OverloadExtensions_Extension &);
    ~OverloadExtensions_Extension();
    OverloadExtensions_Extension & operator = (const OverloadExtensions_Extension &);
    int operator == (const OverloadExtensions_Extension &) const;
    int operator != (const OverloadExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq159   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef OverloadIEs_Value value;

    __seq159();
    __seq159(const __seq159 &);
    __seq159(id, criticality, const value &);

    __seq159 & operator = (const __seq159 &);
    int operator == (const __seq159 &) const;
    int operator != (const __seq159 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq160   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef OverloadExtensions_Extension extensionValue;

    __seq160();
    __seq160(const __seq160 &);
    __seq160(id, criticality, const extensionValue &);

    __seq160 & operator = (const __seq160 &);
    int operator == (const __seq160 &) const;
    int operator != (const __seq160 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC ErrorIndicationIEs_Value : public OssConstrainedOpenType
{
public:
    ErrorIndicationIEs_Value();
    ErrorIndicationIEs_Value(const ErrorIndicationIEs_Value &);
    ~ErrorIndicationIEs_Value();
    ErrorIndicationIEs_Value & operator = (const ErrorIndicationIEs_Value &);
    int operator == (const ErrorIndicationIEs_Value &) const;
    int operator != (const ErrorIndicationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq161   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ErrorIndicationIEs_Value value;

    __seq161();
    __seq161(const __seq161 &);
    __seq161(id, criticality, const value &);

    __seq161 & operator = (const __seq161 &);
    int operator == (const __seq161 &) const;
    int operator != (const __seq161 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC SRNS_DataForwardCommandIEs_Value : public OssConstrainedOpenType
{
public:
    SRNS_DataForwardCommandIEs_Value();
    SRNS_DataForwardCommandIEs_Value(const SRNS_DataForwardCommandIEs_Value &);
    ~SRNS_DataForwardCommandIEs_Value();
    SRNS_DataForwardCommandIEs_Value & operator = (const SRNS_DataForwardCommandIEs_Value &);
    int operator == (const SRNS_DataForwardCommandIEs_Value &) const;
    int operator != (const SRNS_DataForwardCommandIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_DataForwardingList *get_RAB_DataForwardingList();
    const RAB_DataForwardingList *get_RAB_DataForwardingList() const;
    void set_RAB_DataForwardingList(const RAB_DataForwardingList &);
    RAB_DataForwardingList *release_RAB_DataForwardingList();
    void set_RAB_DataForwardingList(RAB_DataForwardingList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq163   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef SRNS_DataForwardCommandIEs_Value value;

    __seq163();
    __seq163(const __seq163 &);
    __seq163(id, criticality, const value &);

    __seq163 & operator = (const __seq163 &);
    int operator == (const __seq163 &) const;
    int operator != (const __seq163 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC ForwardSRNS_ContextIEs_Value : public OssConstrainedOpenType
{
public:
    ForwardSRNS_ContextIEs_Value();
    ForwardSRNS_ContextIEs_Value(const ForwardSRNS_ContextIEs_Value &);
    ~ForwardSRNS_ContextIEs_Value();
    ForwardSRNS_ContextIEs_Value & operator = (const ForwardSRNS_ContextIEs_Value &);
    int operator == (const ForwardSRNS_ContextIEs_Value &) const;
    int operator != (const ForwardSRNS_ContextIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ContextList *get_RAB_ContextList();
    const RAB_ContextList *get_RAB_ContextList() const;
    void set_RAB_ContextList(const RAB_ContextList &);
    RAB_ContextList *release_RAB_ContextList();
    void set_RAB_ContextList(RAB_ContextList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC ForwardSRNS_ContextExtensions_Extension : public OssConstrainedOpenType
{
public:
    ForwardSRNS_ContextExtensions_Extension();
    ForwardSRNS_ContextExtensions_Extension(const ForwardSRNS_ContextExtensions_Extension &);
    ~ForwardSRNS_ContextExtensions_Extension();
    ForwardSRNS_ContextExtensions_Extension & operator = (const ForwardSRNS_ContextExtensions_Extension &);
    int operator == (const ForwardSRNS_ContextExtensions_Extension &) const;
    int operator != (const ForwardSRNS_ContextExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RRC_Container *get_RRC_Container();
    const RRC_Container *get_RRC_Container() const;
    void set_RRC_Container(const RRC_Container &);
    RRC_Container *release_RRC_Container();
    void set_RRC_Container(RRC_Container *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq165   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ForwardSRNS_ContextIEs_Value value;

    __seq165();
    __seq165(const __seq165 &);
    __seq165(id, criticality, const value &);

    __seq165 & operator = (const __seq165 &);
    int operator == (const __seq165 &) const;
    int operator != (const __seq165 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared29   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef ForwardSRNS_ContextExtensions_Extension extensionValue;

    __shared29();
    __shared29(const __shared29 &);
    __shared29(id, criticality, const extensionValue &);

    __shared29 & operator = (const __shared29 &);
    int operator == (const __shared29 &) const;
    int operator != (const __shared29 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __seqof161;

class OSS_PUBLIC RAB_SetupOrModifyList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof161 component;

    RAB_SetupOrModifyList();
    RAB_SetupOrModifyList(const RAB_SetupOrModifyList &);
    ~RAB_SetupOrModifyList();

    RAB_SetupOrModifyList & operator = (const RAB_SetupOrModifyList &);
    int operator == (const RAB_SetupOrModifyList &) const;
    int operator != (const RAB_SetupOrModifyList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_SetupOrModifyList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_SetupOrModifyList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_SetupOrModifyList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_AssignmentRequestIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_AssignmentRequestIEs_Value();
    RAB_AssignmentRequestIEs_Value(const RAB_AssignmentRequestIEs_Value &);
    ~RAB_AssignmentRequestIEs_Value();
    RAB_AssignmentRequestIEs_Value & operator = (const RAB_AssignmentRequestIEs_Value &);
    int operator == (const RAB_AssignmentRequestIEs_Value &) const;
    int operator != (const RAB_AssignmentRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupOrModifyList *get_RAB_SetupOrModifyList();
    const RAB_SetupOrModifyList *get_RAB_SetupOrModifyList() const;
    void set_RAB_SetupOrModifyList(const RAB_SetupOrModifyList &);
    RAB_SetupOrModifyList *release_RAB_SetupOrModifyList();
    void set_RAB_SetupOrModifyList(RAB_SetupOrModifyList *);

    RAB_ReleaseList *get_RAB_ReleaseList();
    const RAB_ReleaseList *get_RAB_ReleaseList() const;
    void set_RAB_ReleaseList(const RAB_ReleaseList &);
    RAB_ReleaseList *release_RAB_ReleaseList();
    void set_RAB_ReleaseList(RAB_ReleaseList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq167   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_AssignmentRequestIEs_Value value;

    __seq167();
    __seq167(const __seq167 &);
    __seq167(id, criticality, const value &);

    __seq167 & operator = (const __seq167 &);
    int operator == (const __seq167 &) const;
    int operator != (const __seq167 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof161 : public OssList  /* SEQUENCE OF */
{
public:
    typedef ProtocolIE_FieldPair component;

    __seqof161();
    __seqof161(const __seqof161 &);
    ~__seqof161();

    __seqof161 & operator = (const __seqof161 &);
    int operator == (const __seqof161 &) const;
    int operator != (const __seqof161 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof161 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof161 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof161 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof167;

class OSS_PUBLIC RAB_SetupOrModifiedList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof167 component;

    RAB_SetupOrModifiedList();
    RAB_SetupOrModifiedList(const RAB_SetupOrModifiedList &);
    ~RAB_SetupOrModifiedList();

    RAB_SetupOrModifiedList & operator = (const RAB_SetupOrModifiedList &);
    int operator == (const RAB_SetupOrModifiedList &) const;
    int operator != (const RAB_SetupOrModifiedList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_SetupOrModifiedList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_SetupOrModifiedList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_SetupOrModifiedList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof169;

class OSS_PUBLIC RAB_ReleasedList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof169 component;

    RAB_ReleasedList();
    RAB_ReleasedList(const RAB_ReleasedList &);
    ~RAB_ReleasedList();

    RAB_ReleasedList & operator = (const RAB_ReleasedList &);
    int operator == (const RAB_ReleasedList &) const;
    int operator != (const RAB_ReleasedList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ReleasedList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ReleasedList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ReleasedList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof172;

class OSS_PUBLIC RAB_QueuedList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof172 component;

    RAB_QueuedList();
    RAB_QueuedList(const RAB_QueuedList &);
    ~RAB_QueuedList();

    RAB_QueuedList & operator = (const RAB_QueuedList &);
    int operator == (const RAB_QueuedList &) const;
    int operator != (const RAB_QueuedList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_QueuedList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_QueuedList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_QueuedList *extract_after(OssIndex, OssIndex);
};

typedef __shared34 RAB_ReleaseFailedList;

class OSS_PUBLIC RAB_AssignmentResponseIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_AssignmentResponseIEs_Value();
    RAB_AssignmentResponseIEs_Value(const RAB_AssignmentResponseIEs_Value &);
    ~RAB_AssignmentResponseIEs_Value();
    RAB_AssignmentResponseIEs_Value & operator = (const RAB_AssignmentResponseIEs_Value &);
    int operator == (const RAB_AssignmentResponseIEs_Value &) const;
    int operator != (const RAB_AssignmentResponseIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupOrModifiedList *get_RAB_SetupOrModifiedList();
    const RAB_SetupOrModifiedList *get_RAB_SetupOrModifiedList() const;
    void set_RAB_SetupOrModifiedList(const RAB_SetupOrModifiedList &);
    RAB_SetupOrModifiedList *release_RAB_SetupOrModifiedList();
    void set_RAB_SetupOrModifiedList(RAB_SetupOrModifiedList *);

    RAB_ReleasedList *get_RAB_ReleasedList();
    const RAB_ReleasedList *get_RAB_ReleasedList() const;
    void set_RAB_ReleasedList(const RAB_ReleasedList &);
    RAB_ReleasedList *release_RAB_ReleasedList();
    void set_RAB_ReleasedList(RAB_ReleasedList *);

    RAB_QueuedList *get_RAB_QueuedList();
    const RAB_QueuedList *get_RAB_QueuedList() const;
    void set_RAB_QueuedList(const RAB_QueuedList &);
    RAB_QueuedList *release_RAB_QueuedList();
    void set_RAB_QueuedList(RAB_QueuedList *);

    __shared34 *get_RAB_FailedList();
    const __shared34 *get_RAB_FailedList() const;
    void set_RAB_FailedList(const __shared34 &);
    __shared34 *release_RAB_FailedList();
    void set_RAB_FailedList(__shared34 *);

    __shared34 *get_RAB_ReleaseFailedList();
    const __shared34 *get_RAB_ReleaseFailedList() const;
    void set_RAB_ReleaseFailedList(const __shared34 &);
    __shared34 *release_RAB_ReleaseFailedList();
    void set_RAB_ReleaseFailedList(__shared34 *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seqof174;

class OSS_PUBLIC GERAN_Iumode_RAB_FailedList_RABAssgntResponse : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof174 component;

    GERAN_Iumode_RAB_FailedList_RABAssgntResponse();
    GERAN_Iumode_RAB_FailedList_RABAssgntResponse(const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    ~GERAN_Iumode_RAB_FailedList_RABAssgntResponse();

    GERAN_Iumode_RAB_FailedList_RABAssgntResponse & operator = (const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    int operator == (const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &) const;
    int operator != (const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(GERAN_Iumode_RAB_FailedList_RABAssgntResponse *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, GERAN_Iumode_RAB_FailedList_RABAssgntResponse *);

    int remove_front();
    int remove_after(OssIndex);

    GERAN_Iumode_RAB_FailedList_RABAssgntResponse *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_AssignmentResponseExtensions_Extension : public OssConstrainedOpenType
{
public:
    RAB_AssignmentResponseExtensions_Extension();
    RAB_AssignmentResponseExtensions_Extension(const RAB_AssignmentResponseExtensions_Extension &);
    ~RAB_AssignmentResponseExtensions_Extension();
    RAB_AssignmentResponseExtensions_Extension & operator = (const RAB_AssignmentResponseExtensions_Extension &);
    int operator == (const RAB_AssignmentResponseExtensions_Extension &) const;
    int operator != (const RAB_AssignmentResponseExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_GERAN_Iumode_RAB_FailedList_RABAssgntResponse();
    const GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_GERAN_Iumode_RAB_FailedList_RABAssgntResponse() const;
    void set_GERAN_Iumode_RAB_FailedList_RABAssgntResponse(const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    GERAN_Iumode_RAB_FailedList_RABAssgntResponse *release_GERAN_Iumode_RAB_FailedList_RABAssgntResponse();
    void set_GERAN_Iumode_RAB_FailedList_RABAssgntResponse(GERAN_Iumode_RAB_FailedList_RABAssgntResponse *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq172   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_AssignmentResponseIEs_Value value;

    __seq172();
    __seq172(const __seq172 &);
    __seq172(id, criticality, const value &);

    __seq172 & operator = (const __seq172 &);
    int operator == (const __seq172 &) const;
    int operator != (const __seq172 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq173   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_AssignmentResponseExtensions_Extension extensionValue;

    __seq173();
    __seq173(const __seq173 &);
    __seq173(id, criticality, const extensionValue &);

    __seq173 & operator = (const __seq173 &);
    int operator == (const __seq173 &) const;
    int operator != (const __seq173 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC __seq175;

class OSS_PUBLIC __seqof168 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq175 component;

    __seqof168();
    __seqof168(const __seqof168 &);
    ~__seqof168();

    __seqof168 & operator = (const __seqof168 &);
    int operator == (const __seqof168 &) const;
    int operator != (const __seqof168 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof168 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof168 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof168 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_SetupOrModifiedItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef OssBitString transportLayerAddress;
    typedef IuTransportAssociation iuTransportAssociation;
    typedef __shared31 dl_dataVolumes;
    typedef __seqof168 iE_Extensions;

    RAB_SetupOrModifiedItem();
    RAB_SetupOrModifiedItem(const RAB_SetupOrModifiedItem &);
    RAB_SetupOrModifiedItem(const rAB_ID &, const transportLayerAddress &, const iuTransportAssociation &, 
	const dl_dataVolumes &, const iE_Extensions &);
    RAB_SetupOrModifiedItem(const rAB_ID &);

    RAB_SetupOrModifiedItem & operator = (const RAB_SetupOrModifiedItem &);
    int operator == (const RAB_SetupOrModifiedItem &) const;
    int operator != (const RAB_SetupOrModifiedItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    transportLayerAddress *get_transportLayerAddress();
    const transportLayerAddress *get_transportLayerAddress() const;
    void set_transportLayerAddress(const transportLayerAddress &);
    int transportLayerAddress_is_present() const;
    void omit_transportLayerAddress();

    iuTransportAssociation *get_iuTransportAssociation();
    const iuTransportAssociation *get_iuTransportAssociation() const;
    void set_iuTransportAssociation(const iuTransportAssociation &);
    int iuTransportAssociation_is_present() const;
    void omit_iuTransportAssociation();

    dl_dataVolumes *get_dl_dataVolumes();
    const dl_dataVolumes *get_dl_dataVolumes() const;
    void set_dl_dataVolumes(const dl_dataVolumes &);
    int dl_dataVolumes_is_present() const;
    void omit_dl_dataVolumes();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    transportLayerAddress transportLayerAddress_field;
    iuTransportAssociation iuTransportAssociation_field;
    dl_dataVolumes dl_dataVolumes_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_SetupOrModifiedItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_SetupOrModifiedItemIEs_Value();
    RAB_SetupOrModifiedItemIEs_Value(const RAB_SetupOrModifiedItemIEs_Value &);
    ~RAB_SetupOrModifiedItemIEs_Value();
    RAB_SetupOrModifiedItemIEs_Value & operator = (const RAB_SetupOrModifiedItemIEs_Value &);
    int operator == (const RAB_SetupOrModifiedItemIEs_Value &) const;
    int operator != (const RAB_SetupOrModifiedItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_SetupOrModifiedItem *get_RAB_SetupOrModifiedItem();
    const RAB_SetupOrModifiedItem *get_RAB_SetupOrModifiedItem() const;
    void set_RAB_SetupOrModifiedItem(const RAB_SetupOrModifiedItem &);
    RAB_SetupOrModifiedItem *release_RAB_SetupOrModifiedItem();
    void set_RAB_SetupOrModifiedItem(RAB_SetupOrModifiedItem *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq174;

class OSS_PUBLIC __seqof167 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq174 component;

    __seqof167();
    __seqof167(const __seqof167 &);
    ~__seqof167();

    __seqof167 & operator = (const __seqof167 &);
    int operator == (const __seqof167 &) const;
    int operator != (const __seqof167 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof167 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof167 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof167 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq174   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupOrModifiedItemIEs_Value value;

    __seq174();
    __seq174(const __seq174 &);
    __seq174(id, criticality, const value &);

    __seq174 & operator = (const __seq174 &);
    int operator == (const __seq174 &) const;
    int operator != (const __seq174 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_SetupOrModifiedItem_ExtIEs_Extension : public OssConstrainedOpenType
{
public:
    RAB_SetupOrModifiedItem_ExtIEs_Extension();
    RAB_SetupOrModifiedItem_ExtIEs_Extension(const RAB_SetupOrModifiedItem_ExtIEs_Extension &);
    ~RAB_SetupOrModifiedItem_ExtIEs_Extension();
    RAB_SetupOrModifiedItem_ExtIEs_Extension & operator = (const RAB_SetupOrModifiedItem_ExtIEs_Extension &);
    int operator == (const RAB_SetupOrModifiedItem_ExtIEs_Extension &) const;
    int operator != (const RAB_SetupOrModifiedItem_ExtIEs_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    Ass_RAB_Parameters *get_Ass_RAB_Parameters();
    const Ass_RAB_Parameters *get_Ass_RAB_Parameters() const;
    void set_Ass_RAB_Parameters(const Ass_RAB_Parameters &);
    Ass_RAB_Parameters *release_Ass_RAB_Parameters();
    void set_Ass_RAB_Parameters(Ass_RAB_Parameters *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq175   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_SetupOrModifiedItem_ExtIEs_Extension extensionValue;

    __seq175();
    __seq175(const __seq175 &);
    __seq175(id, criticality, const extensionValue &);

    __seq175 & operator = (const __seq175 &);
    int operator == (const __seq175 &) const;
    int operator != (const __seq175 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC RAB_ReleasedItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef __shared31 dl_dataVolumes;
    typedef OSS_UINT32 dL_GTP_PDU_SequenceNumber;
    typedef OSS_UINT32 uL_GTP_PDU_SequenceNumber;
    typedef __shared4 iE_Extensions;

    RAB_ReleasedItem();
    RAB_ReleasedItem(const RAB_ReleasedItem &);
    RAB_ReleasedItem(const rAB_ID &, const dl_dataVolumes &, dL_GTP_PDU_SequenceNumber, 
	uL_GTP_PDU_SequenceNumber, const iE_Extensions &);
    RAB_ReleasedItem(const rAB_ID &);

    RAB_ReleasedItem & operator = (const RAB_ReleasedItem &);
    int operator == (const RAB_ReleasedItem &) const;
    int operator != (const RAB_ReleasedItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    dl_dataVolumes *get_dl_dataVolumes();
    const dl_dataVolumes *get_dl_dataVolumes() const;
    void set_dl_dataVolumes(const dl_dataVolumes &);
    int dl_dataVolumes_is_present() const;
    void omit_dl_dataVolumes();

    dL_GTP_PDU_SequenceNumber *get_dL_GTP_PDU_SequenceNumber();
    const dL_GTP_PDU_SequenceNumber *get_dL_GTP_PDU_SequenceNumber() const;
    void set_dL_GTP_PDU_SequenceNumber(dL_GTP_PDU_SequenceNumber);
    int dL_GTP_PDU_SequenceNumber_is_present() const;
    void omit_dL_GTP_PDU_SequenceNumber();

    uL_GTP_PDU_SequenceNumber *get_uL_GTP_PDU_SequenceNumber();
    const uL_GTP_PDU_SequenceNumber *get_uL_GTP_PDU_SequenceNumber() const;
    void set_uL_GTP_PDU_SequenceNumber(uL_GTP_PDU_SequenceNumber);
    int uL_GTP_PDU_SequenceNumber_is_present() const;
    void omit_uL_GTP_PDU_SequenceNumber();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    dl_dataVolumes dl_dataVolumes_field;
    dL_GTP_PDU_SequenceNumber dL_GTP_PDU_SequenceNumber_field;
    uL_GTP_PDU_SequenceNumber uL_GTP_PDU_SequenceNumber_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_ReleasedItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ReleasedItemIEs_Value();
    RAB_ReleasedItemIEs_Value(const RAB_ReleasedItemIEs_Value &);
    ~RAB_ReleasedItemIEs_Value();
    RAB_ReleasedItemIEs_Value & operator = (const RAB_ReleasedItemIEs_Value &);
    int operator == (const RAB_ReleasedItemIEs_Value &) const;
    int operator != (const RAB_ReleasedItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ReleasedItem *get_RAB_ReleasedItem();
    const RAB_ReleasedItem *get_RAB_ReleasedItem() const;
    void set_RAB_ReleasedItem(const RAB_ReleasedItem &);
    RAB_ReleasedItem *release_RAB_ReleasedItem();
    void set_RAB_ReleasedItem(RAB_ReleasedItem *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq176;

class OSS_PUBLIC __seqof169 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq176 component;

    __seqof169();
    __seqof169(const __seqof169 &);
    ~__seqof169();

    __seqof169 & operator = (const __seqof169 &);
    int operator == (const __seqof169 &) const;
    int operator != (const __seqof169 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof169 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof169 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof169 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq176   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ReleasedItemIEs_Value value;

    __seq176();
    __seq176(const __seq176 &);
    __seq176(id, criticality, const value &);

    __seq176 & operator = (const __seq176 &);
    int operator == (const __seq176 &) const;
    int operator != (const __seq176 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq179   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 dl_UnsuccessfullyTransmittedDataVolume;
    typedef OSS_UINT32 dataVolumeReference;
    typedef __shared4 iE_Extensions;

    __seq179();
    __seq179(const __seq179 &);
    __seq179(dl_UnsuccessfullyTransmittedDataVolume, dataVolumeReference, const iE_Extensions &);
    __seq179(dl_UnsuccessfullyTransmittedDataVolume);

    __seq179 & operator = (const __seq179 &);
    int operator == (const __seq179 &) const;
    int operator != (const __seq179 &) const;

    dl_UnsuccessfullyTransmittedDataVolume & get_dl_UnsuccessfullyTransmittedDataVolume();
    dl_UnsuccessfullyTransmittedDataVolume get_dl_UnsuccessfullyTransmittedDataVolume() const;
    void set_dl_UnsuccessfullyTransmittedDataVolume(dl_UnsuccessfullyTransmittedDataVolume);

    dataVolumeReference *get_dataVolumeReference();
    const dataVolumeReference *get_dataVolumeReference() const;
    void set_dataVolumeReference(dataVolumeReference);
    int dataVolumeReference_is_present() const;
    void omit_dataVolumeReference();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    dl_UnsuccessfullyTransmittedDataVolume dl_UnsuccessfullyTransmittedDataVolume_field;
    dataVolumeReference dataVolumeReference_field;
    iE_Extensions iE_Extensions_field;
};

typedef __shared16 RAB_QueuedItem;

class OSS_PUBLIC RAB_QueuedItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_QueuedItemIEs_Value();
    RAB_QueuedItemIEs_Value(const RAB_QueuedItemIEs_Value &);
    ~RAB_QueuedItemIEs_Value();
    RAB_QueuedItemIEs_Value & operator = (const RAB_QueuedItemIEs_Value &);
    int operator == (const RAB_QueuedItemIEs_Value &) const;
    int operator != (const RAB_QueuedItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared16 *get_RAB_QueuedItem();
    const __shared16 *get_RAB_QueuedItem() const;
    void set_RAB_QueuedItem(const __shared16 &);
    __shared16 *release_RAB_QueuedItem();
    void set_RAB_QueuedItem(__shared16 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq180;

class OSS_PUBLIC __seqof172 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq180 component;

    __seqof172();
    __seqof172(const __seqof172 &);
    ~__seqof172();

    __seqof172 & operator = (const __seqof172 &);
    int operator == (const __seqof172 &) const;
    int operator != (const __seqof172 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof172 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof172 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof172 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq180   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_QueuedItemIEs_Value value;

    __seq180();
    __seq180(const __seq180 &);
    __seq180(id, criticality, const value &);

    __seq180 & operator = (const __seq180 &);
    int operator == (const __seq180 &) const;
    int operator != (const __seq180 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef Cause cause;
    typedef OssString gERAN_Classmark;
    typedef __shared4 iE_Extensions;

    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item();
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(const rAB_ID &, const cause &, 
	const gERAN_Classmark &, const iE_Extensions &);
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(const rAB_ID &, const cause &);

    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item & operator = (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    int operator == (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &) const;
    int operator != (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    cause & get_cause();
    const cause & get_cause() const;
    void set_cause(const cause &);

    gERAN_Classmark *get_gERAN_Classmark();
    const gERAN_Classmark *get_gERAN_Classmark() const;
    void set_gERAN_Classmark(const gERAN_Classmark &);
    int gERAN_Classmark_is_present() const;
    void omit_gERAN_Classmark();

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    cause cause_field;
    gERAN_Classmark gERAN_Classmark_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value : public OssConstrainedOpenType
{
public:
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value();
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value(const GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value &);
    ~GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value();
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value & operator = (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value &);
    int operator == (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value &) const;
    int operator != (const GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item();
    const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item() const;
    void set_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *release_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item();
    void set_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq182;

class OSS_PUBLIC __seqof174 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq182 component;

    __seqof174();
    __seqof174(const __seqof174 &);
    ~__seqof174();

    __seqof174 & operator = (const __seqof174 &);
    int operator == (const __seqof174 &) const;
    int operator != (const __seqof174 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof174 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof174 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof174 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq182   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef GERAN_Iumode_RAB_Failed_RABAssgntResponse_ItemIEs_Value value;

    __seq182();
    __seq182(const __seq182 &);
    __seq182(id, criticality, const value &);

    __seq182 & operator = (const __seq182 &);
    int operator == (const __seq182 &) const;
    int operator != (const __seq182 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof179;

class OSS_PUBLIC DirectTransferInformationList_RANAP_RelocInf : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof179 component;

    DirectTransferInformationList_RANAP_RelocInf();
    DirectTransferInformationList_RANAP_RelocInf(const DirectTransferInformationList_RANAP_RelocInf &);
    ~DirectTransferInformationList_RANAP_RelocInf();

    DirectTransferInformationList_RANAP_RelocInf & operator = (const DirectTransferInformationList_RANAP_RelocInf &);
    int operator == (const DirectTransferInformationList_RANAP_RelocInf &) const;
    int operator != (const DirectTransferInformationList_RANAP_RelocInf &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(DirectTransferInformationList_RANAP_RelocInf *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, DirectTransferInformationList_RANAP_RelocInf *);

    int remove_front();
    int remove_after(OssIndex);

    DirectTransferInformationList_RANAP_RelocInf *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seqof181;

class OSS_PUBLIC RAB_ContextList_RANAP_RelocInf : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof181 component;

    RAB_ContextList_RANAP_RelocInf();
    RAB_ContextList_RANAP_RelocInf(const RAB_ContextList_RANAP_RelocInf &);
    ~RAB_ContextList_RANAP_RelocInf();

    RAB_ContextList_RANAP_RelocInf & operator = (const RAB_ContextList_RANAP_RelocInf &);
    int operator == (const RAB_ContextList_RANAP_RelocInf &) const;
    int operator != (const RAB_ContextList_RANAP_RelocInf &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ContextList_RANAP_RelocInf *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ContextList_RANAP_RelocInf *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ContextList_RANAP_RelocInf *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RANAP_RelocationInformationIEs_Value : public OssConstrainedOpenType
{
public:
    RANAP_RelocationInformationIEs_Value();
    RANAP_RelocationInformationIEs_Value(const RANAP_RelocationInformationIEs_Value &);
    ~RANAP_RelocationInformationIEs_Value();
    RANAP_RelocationInformationIEs_Value & operator = (const RANAP_RelocationInformationIEs_Value &);
    int operator == (const RANAP_RelocationInformationIEs_Value &) const;
    int operator != (const RANAP_RelocationInformationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    DirectTransferInformationList_RANAP_RelocInf *get_DirectTransferInformationList_RANAP_RelocInf();
    const DirectTransferInformationList_RANAP_RelocInf *get_DirectTransferInformationList_RANAP_RelocInf() const;
    void set_DirectTransferInformationList_RANAP_RelocInf(const DirectTransferInformationList_RANAP_RelocInf &);
    DirectTransferInformationList_RANAP_RelocInf *release_DirectTransferInformationList_RANAP_RelocInf();
    void set_DirectTransferInformationList_RANAP_RelocInf(DirectTransferInformationList_RANAP_RelocInf *);

    RAB_ContextList_RANAP_RelocInf *get_RAB_ContextList_RANAP_RelocInf();
    const RAB_ContextList_RANAP_RelocInf *get_RAB_ContextList_RANAP_RelocInf() const;
    void set_RAB_ContextList_RANAP_RelocInf(const RAB_ContextList_RANAP_RelocInf &);
    RAB_ContextList_RANAP_RelocInf *release_RAB_ContextList_RANAP_RelocInf();
    void set_RAB_ContextList_RANAP_RelocInf(RAB_ContextList_RANAP_RelocInf *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq184   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RANAP_RelocationInformationIEs_Value value;

    __seq184();
    __seq184(const __seq184 &);
    __seq184(id, criticality, const value &);

    __seq184 & operator = (const __seq184 &);
    int operator == (const __seq184 &) const;
    int operator != (const __seq184 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC DirectTransferInformationItem_RANAP_RelocInf   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssString nAS_PDU;
    typedef enum SAPI sAPI;
    typedef enum CN_DomainIndicator cN_DomainIndicator;
    typedef __shared4 iE_Extensions;

    DirectTransferInformationItem_RANAP_RelocInf();
    DirectTransferInformationItem_RANAP_RelocInf(const DirectTransferInformationItem_RANAP_RelocInf &);
    DirectTransferInformationItem_RANAP_RelocInf(const nAS_PDU &, sAPI, cN_DomainIndicator, 
	const iE_Extensions &);
    DirectTransferInformationItem_RANAP_RelocInf(const nAS_PDU &, sAPI, cN_DomainIndicator);

    DirectTransferInformationItem_RANAP_RelocInf & operator = (const DirectTransferInformationItem_RANAP_RelocInf &);
    int operator == (const DirectTransferInformationItem_RANAP_RelocInf &) const;
    int operator != (const DirectTransferInformationItem_RANAP_RelocInf &) const;

    nAS_PDU & get_nAS_PDU();
    const nAS_PDU & get_nAS_PDU() const;
    void set_nAS_PDU(const nAS_PDU &);

    sAPI & get_sAPI();
    sAPI get_sAPI() const;
    void set_sAPI(sAPI);

    cN_DomainIndicator & get_cN_DomainIndicator();
    cN_DomainIndicator get_cN_DomainIndicator() const;
    void set_cN_DomainIndicator(cN_DomainIndicator);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    nAS_PDU nAS_PDU_field;
    sAPI sAPI_field;
    cN_DomainIndicator cN_DomainIndicator_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC DirectTransferInformationItemIEs_RANAP_RelocInf_Value : public OssConstrainedOpenType
{
public:
    DirectTransferInformationItemIEs_RANAP_RelocInf_Value();
    DirectTransferInformationItemIEs_RANAP_RelocInf_Value(const DirectTransferInformationItemIEs_RANAP_RelocInf_Value &);
    ~DirectTransferInformationItemIEs_RANAP_RelocInf_Value();
    DirectTransferInformationItemIEs_RANAP_RelocInf_Value & operator = (const DirectTransferInformationItemIEs_RANAP_RelocInf_Value &);
    int operator == (const DirectTransferInformationItemIEs_RANAP_RelocInf_Value &) const;
    int operator != (const DirectTransferInformationItemIEs_RANAP_RelocInf_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    DirectTransferInformationItem_RANAP_RelocInf *get_DirectTransferInformationItem_RANAP_RelocInf();
    const DirectTransferInformationItem_RANAP_RelocInf *get_DirectTransferInformationItem_RANAP_RelocInf() const;
    void set_DirectTransferInformationItem_RANAP_RelocInf(const DirectTransferInformationItem_RANAP_RelocInf &);
    DirectTransferInformationItem_RANAP_RelocInf *release_DirectTransferInformationItem_RANAP_RelocInf();
    void set_DirectTransferInformationItem_RANAP_RelocInf(DirectTransferInformationItem_RANAP_RelocInf *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq186;

class OSS_PUBLIC __seqof179 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq186 component;

    __seqof179();
    __seqof179(const __seqof179 &);
    ~__seqof179();

    __seqof179 & operator = (const __seqof179 &);
    int operator == (const __seqof179 &) const;
    int operator != (const __seqof179 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof179 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof179 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof179 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq186   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef DirectTransferInformationItemIEs_RANAP_RelocInf_Value value;

    __seq186();
    __seq186(const __seq186 &);
    __seq186(id, criticality, const value &);

    __seq186 & operator = (const __seq186 &);
    int operator == (const __seq186 &) const;
    int operator != (const __seq186 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

typedef __shared28 RAB_ContextItem_RANAP_RelocInf;

class OSS_PUBLIC RAB_ContextItemIEs_RANAP_RelocInf_Value : public OssConstrainedOpenType
{
public:
    RAB_ContextItemIEs_RANAP_RelocInf_Value();
    RAB_ContextItemIEs_RANAP_RelocInf_Value(const RAB_ContextItemIEs_RANAP_RelocInf_Value &);
    ~RAB_ContextItemIEs_RANAP_RelocInf_Value();
    RAB_ContextItemIEs_RANAP_RelocInf_Value & operator = (const RAB_ContextItemIEs_RANAP_RelocInf_Value &);
    int operator == (const RAB_ContextItemIEs_RANAP_RelocInf_Value &) const;
    int operator != (const RAB_ContextItemIEs_RANAP_RelocInf_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    __shared28 *get_RAB_ContextItem_RANAP_RelocInf();
    const __shared28 *get_RAB_ContextItem_RANAP_RelocInf() const;
    void set_RAB_ContextItem_RANAP_RelocInf(const __shared28 &);
    __shared28 *release_RAB_ContextItem_RANAP_RelocInf();
    void set_RAB_ContextItem_RANAP_RelocInf(__shared28 *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq188;

class OSS_PUBLIC __seqof181 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq188 component;

    __seqof181();
    __seqof181(const __seqof181 &);
    ~__seqof181();

    __seqof181 & operator = (const __seqof181 &);
    int operator == (const __seqof181 &) const;
    int operator != (const __seqof181 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof181 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof181 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof181 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq188   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ContextItemIEs_RANAP_RelocInf_Value value;

    __seq188();
    __seq188(const __seq188 &);
    __seq188(id, criticality, const value &);

    __seq188 & operator = (const __seq188 &);
    int operator == (const __seq188 &) const;
    int operator != (const __seq188 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seqof185;

class OSS_PUBLIC RAB_ModifyList : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seqof185 component;

    RAB_ModifyList();
    RAB_ModifyList(const RAB_ModifyList &);
    ~RAB_ModifyList();

    RAB_ModifyList & operator = (const RAB_ModifyList &);
    int operator == (const RAB_ModifyList &) const;
    int operator != (const RAB_ModifyList &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(RAB_ModifyList *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, RAB_ModifyList *);

    int remove_front();
    int remove_after(OssIndex);

    RAB_ModifyList *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_ModifyRequestIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ModifyRequestIEs_Value();
    RAB_ModifyRequestIEs_Value(const RAB_ModifyRequestIEs_Value &);
    ~RAB_ModifyRequestIEs_Value();
    RAB_ModifyRequestIEs_Value & operator = (const RAB_ModifyRequestIEs_Value &);
    int operator == (const RAB_ModifyRequestIEs_Value &) const;
    int operator != (const RAB_ModifyRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ModifyList *get_RAB_ModifyList();
    const RAB_ModifyList *get_RAB_ModifyList() const;
    void set_RAB_ModifyList(const RAB_ModifyList &);
    RAB_ModifyList *release_RAB_ModifyList();
    void set_RAB_ModifyList(RAB_ModifyList *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq190;

class OSS_PUBLIC __seqof183 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq190 component;

    __seqof183();
    __seqof183(const __seqof183 &);
    ~__seqof183();

    __seqof183 & operator = (const __seqof183 &);
    int operator == (const __seqof183 &) const;
    int operator != (const __seqof183 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof183 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof183 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof183 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC RAB_ModifyRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof183 protocolIEs;
    typedef __shared4 protocolExtensions;

    RAB_ModifyRequest();
    RAB_ModifyRequest(const RAB_ModifyRequest &);
    RAB_ModifyRequest(const protocolIEs &, const protocolExtensions &);
    RAB_ModifyRequest(const protocolIEs &);

    RAB_ModifyRequest & operator = (const RAB_ModifyRequest &);
    int operator == (const RAB_ModifyRequest &) const;
    int operator != (const RAB_ModifyRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq190   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ModifyRequestIEs_Value value;

    __seq190();
    __seq190(const __seq190 &);
    __seq190(id, criticality, const value &);

    __seq190 & operator = (const __seq190 &);
    int operator == (const __seq190 &) const;
    int operator != (const __seq190 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC RAB_ModifyItem   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OssBitString rAB_ID;
    typedef Requested_RAB_Parameter_Values requested_RAB_Parameter_Values;
    typedef __shared4 iE_Extensions;

    RAB_ModifyItem();
    RAB_ModifyItem(const RAB_ModifyItem &);
    RAB_ModifyItem(const rAB_ID &, const requested_RAB_Parameter_Values &, const iE_Extensions &);
    RAB_ModifyItem(const rAB_ID &, const requested_RAB_Parameter_Values &);

    RAB_ModifyItem & operator = (const RAB_ModifyItem &);
    int operator == (const RAB_ModifyItem &) const;
    int operator != (const RAB_ModifyItem &) const;

    rAB_ID & get_rAB_ID();
    const rAB_ID & get_rAB_ID() const;
    void set_rAB_ID(const rAB_ID &);

    requested_RAB_Parameter_Values & get_requested_RAB_Parameter_Values();
    const requested_RAB_Parameter_Values & get_requested_RAB_Parameter_Values() const;
    void set_requested_RAB_Parameter_Values(const requested_RAB_Parameter_Values &);

    iE_Extensions *get_iE_Extensions();
    const iE_Extensions *get_iE_Extensions() const;
    void set_iE_Extensions(const iE_Extensions &);
    int iE_Extensions_is_present() const;
    void omit_iE_Extensions();
private:
    OSS_UINT32 bit_mask;
    rAB_ID rAB_ID_field;
    requested_RAB_Parameter_Values requested_RAB_Parameter_Values_field;
    iE_Extensions iE_Extensions_field;
};

class OSS_PUBLIC RAB_ModifyItemIEs_Value : public OssConstrainedOpenType
{
public:
    RAB_ModifyItemIEs_Value();
    RAB_ModifyItemIEs_Value(const RAB_ModifyItemIEs_Value &);
    ~RAB_ModifyItemIEs_Value();
    RAB_ModifyItemIEs_Value & operator = (const RAB_ModifyItemIEs_Value &);
    int operator == (const RAB_ModifyItemIEs_Value &) const;
    int operator != (const RAB_ModifyItemIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    RAB_ModifyItem *get_RAB_ModifyItem();
    const RAB_ModifyItem *get_RAB_ModifyItem() const;
    void set_RAB_ModifyItem(const RAB_ModifyItem &);
    RAB_ModifyItem *release_RAB_ModifyItem();
    void set_RAB_ModifyItem(RAB_ModifyItem *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq192;

class OSS_PUBLIC __seqof185 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq192 component;

    __seqof185();
    __seqof185(const __seqof185 &);
    ~__seqof185();

    __seqof185 & operator = (const __seqof185 &);
    int operator == (const __seqof185 &) const;
    int operator != (const __seqof185 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof185 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof185 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof185 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq192   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RAB_ModifyItemIEs_Value value;

    __seq192();
    __seq192(const __seq192 &);
    __seq192(id, criticality, const value &);

    __seq192 & operator = (const __seq192 &);
    int operator == (const __seq192 &) const;
    int operator != (const __seq192 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC LocationRelatedDataRequestIEs_Value : public OssConstrainedOpenType
{
public:
    LocationRelatedDataRequestIEs_Value();
    LocationRelatedDataRequestIEs_Value(const LocationRelatedDataRequestIEs_Value &);
    ~LocationRelatedDataRequestIEs_Value();
    LocationRelatedDataRequestIEs_Value & operator = (const LocationRelatedDataRequestIEs_Value &);
    int operator == (const LocationRelatedDataRequestIEs_Value &) const;
    int operator != (const LocationRelatedDataRequestIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    LocationRelatedDataRequestType *get_LocationRelatedDataRequestType();
    const LocationRelatedDataRequestType *get_LocationRelatedDataRequestType() const;
    void set_LocationRelatedDataRequestType(const LocationRelatedDataRequestType &);
    LocationRelatedDataRequestType *release_LocationRelatedDataRequestType();
    void set_LocationRelatedDataRequestType(LocationRelatedDataRequestType *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC LocationRelatedDataRequestExtensions_Extension : public OssConstrainedOpenType
{
public:
    LocationRelatedDataRequestExtensions_Extension();
    LocationRelatedDataRequestExtensions_Extension(const LocationRelatedDataRequestExtensions_Extension &);
    ~LocationRelatedDataRequestExtensions_Extension();
    LocationRelatedDataRequestExtensions_Extension & operator = (const LocationRelatedDataRequestExtensions_Extension &);
    int operator == (const LocationRelatedDataRequestExtensions_Extension &) const;
    int operator != (const LocationRelatedDataRequestExtensions_Extension &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_LocationRelatedDataRequestTypeSpecificToGERANIuMode();
    const LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_LocationRelatedDataRequestTypeSpecificToGERANIuMode() const;
    void set_LocationRelatedDataRequestTypeSpecificToGERANIuMode(const LocationRelatedDataRequestTypeSpecificToGERANIuMode &);
    LocationRelatedDataRequestTypeSpecificToGERANIuMode *release_LocationRelatedDataRequestTypeSpecificToGERANIuMode();
    void set_LocationRelatedDataRequestTypeSpecificToGERANIuMode(LocationRelatedDataRequestTypeSpecificToGERANIuMode *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq194;

class OSS_PUBLIC __seqof187 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq194 component;

    __seqof187();
    __seqof187(const __seqof187 &);
    ~__seqof187();

    __seqof187 & operator = (const __seqof187 &);
    int operator == (const __seqof187 &) const;
    int operator != (const __seqof187 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof187 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof187 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof187 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __seq195;

class OSS_PUBLIC __seqof188 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq195 component;

    __seqof188();
    __seqof188(const __seqof188 &);
    ~__seqof188();

    __seqof188 & operator = (const __seqof188 &);
    int operator == (const __seqof188 &) const;
    int operator != (const __seqof188 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof188 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof188 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof188 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC LocationRelatedDataRequest   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof187 protocolIEs;
    typedef __seqof188 protocolExtensions;

    LocationRelatedDataRequest();
    LocationRelatedDataRequest(const LocationRelatedDataRequest &);
    LocationRelatedDataRequest(const protocolIEs &, const protocolExtensions &);
    LocationRelatedDataRequest(const protocolIEs &);

    LocationRelatedDataRequest & operator = (const LocationRelatedDataRequest &);
    int operator == (const LocationRelatedDataRequest &) const;
    int operator != (const LocationRelatedDataRequest &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq194   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationRelatedDataRequestIEs_Value value;

    __seq194();
    __seq194(const __seq194 &);
    __seq194(id, criticality, const value &);

    __seq194 & operator = (const __seq194 &);
    int operator == (const __seq194 &) const;
    int operator != (const __seq194 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __seq195   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationRelatedDataRequestExtensions_Extension extensionValue;

    __seq195();
    __seq195(const __seq195 &);
    __seq195(id, criticality, const extensionValue &);

    __seq195 & operator = (const __seq195 &);
    int operator == (const __seq195 &) const;
    int operator != (const __seq195 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC LocationRelatedDataResponseIEs_Value : public OssConstrainedOpenType
{
public:
    LocationRelatedDataResponseIEs_Value();
    LocationRelatedDataResponseIEs_Value(const LocationRelatedDataResponseIEs_Value &);
    ~LocationRelatedDataResponseIEs_Value();
    LocationRelatedDataResponseIEs_Value & operator = (const LocationRelatedDataResponseIEs_Value &);
    int operator == (const LocationRelatedDataResponseIEs_Value &) const;
    int operator != (const LocationRelatedDataResponseIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    BroadcastAssistanceDataDecipheringKeys *get_BroadcastAssistanceDataDecipheringKeys();
    const BroadcastAssistanceDataDecipheringKeys *get_BroadcastAssistanceDataDecipheringKeys() const;
    void set_BroadcastAssistanceDataDecipheringKeys(const BroadcastAssistanceDataDecipheringKeys &);
    BroadcastAssistanceDataDecipheringKeys *release_BroadcastAssistanceDataDecipheringKeys();
    void set_BroadcastAssistanceDataDecipheringKeys(BroadcastAssistanceDataDecipheringKeys *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq196;

class OSS_PUBLIC __seqof189 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq196 component;

    __seqof189();
    __seqof189(const __seqof189 &);
    ~__seqof189();

    __seqof189 & operator = (const __seqof189 &);
    int operator == (const __seqof189 &) const;
    int operator != (const __seqof189 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof189 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof189 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof189 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC __shared37;

class OSS_PUBLIC __shared38 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __shared37 component;

    __shared38();
    __shared38(const __shared38 &);
    ~__shared38();

    __shared38 & operator = (const __shared38 &);
    int operator == (const __shared38 &) const;
    int operator != (const __shared38 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__shared38 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __shared38 *);

    int remove_front();
    int remove_after(OssIndex);

    __shared38 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC LocationRelatedDataResponse   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof189 protocolIEs;
    typedef __shared38 protocolExtensions;

    LocationRelatedDataResponse();
    LocationRelatedDataResponse(const LocationRelatedDataResponse &);
    LocationRelatedDataResponse(const protocolIEs &, const protocolExtensions &);
    LocationRelatedDataResponse(const protocolIEs &);

    LocationRelatedDataResponse & operator = (const LocationRelatedDataResponse &);
    int operator == (const LocationRelatedDataResponse &) const;
    int operator != (const LocationRelatedDataResponse &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq196   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef LocationRelatedDataResponseIEs_Value value;

    __seq196();
    __seq196(const __seq196 &);
    __seq196(id, criticality, const value &);

    __seq196 & operator = (const __seq196 &);
    int operator == (const __seq196 &) const;
    int operator != (const __seq196 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC __shared37   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef RelocationCancelAcknowledgeIEs_Value extensionValue;

    __shared37();
    __shared37(const __shared37 &);
    __shared37(id, criticality, const extensionValue &);

    __shared37 & operator = (const __shared37 &);
    int operator == (const __shared37 &) const;
    int operator != (const __shared37 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    extensionValue & get_extensionValue();
    const extensionValue & get_extensionValue() const;
    void set_extensionValue(const extensionValue &);
private:
    id id_field;
    criticality criticality_field;
    extensionValue extensionValue_field;
};

class OSS_PUBLIC LocationRelatedDataFailure   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __shared2 protocolIEs;
    typedef __shared38 protocolExtensions;

    LocationRelatedDataFailure();
    LocationRelatedDataFailure(const LocationRelatedDataFailure &);
    LocationRelatedDataFailure(const protocolIEs &, const protocolExtensions &);
    LocationRelatedDataFailure(const protocolIEs &);

    LocationRelatedDataFailure & operator = (const LocationRelatedDataFailure &);
    int operator == (const LocationRelatedDataFailure &) const;
    int operator != (const LocationRelatedDataFailure &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC InformationTransferIndicationIEs_Value : public OssConstrainedOpenType
{
public:
    InformationTransferIndicationIEs_Value();
    InformationTransferIndicationIEs_Value(const InformationTransferIndicationIEs_Value &);
    ~InformationTransferIndicationIEs_Value();
    InformationTransferIndicationIEs_Value & operator = (const InformationTransferIndicationIEs_Value &);
    int operator == (const InformationTransferIndicationIEs_Value &) const;
    int operator != (const InformationTransferIndicationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    ProvidedData *get_ProvidedData();
    const ProvidedData *get_ProvidedData() const;
    void set_ProvidedData(const ProvidedData &);
    ProvidedData *release_ProvidedData();
    void set_ProvidedData(ProvidedData *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq200;

class OSS_PUBLIC __seqof193 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq200 component;

    __seqof193();
    __seqof193(const __seqof193 &);
    ~__seqof193();

    __seqof193 & operator = (const __seqof193 &);
    int operator == (const __seqof193 &) const;
    int operator != (const __seqof193 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof193 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof193 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof193 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC InformationTransferIndication   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof193 protocolIEs;
    typedef __shared4 protocolExtensions;

    InformationTransferIndication();
    InformationTransferIndication(const InformationTransferIndication &);
    InformationTransferIndication(const protocolIEs &, const protocolExtensions &);
    InformationTransferIndication(const protocolIEs &);

    InformationTransferIndication & operator = (const InformationTransferIndication &);
    int operator == (const InformationTransferIndication &) const;
    int operator != (const InformationTransferIndication &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq200   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef InformationTransferIndicationIEs_Value value;

    __seq200();
    __seq200(const __seq200 &);
    __seq200(id, criticality, const value &);

    __seq200 & operator = (const __seq200 &);
    int operator == (const __seq200 &) const;
    int operator != (const __seq200 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC InformationTransferConfirmationIEs_Value : public OssConstrainedOpenType
{
public:
    InformationTransferConfirmationIEs_Value();
    InformationTransferConfirmationIEs_Value(const InformationTransferConfirmationIEs_Value &);
    ~InformationTransferConfirmationIEs_Value();
    InformationTransferConfirmationIEs_Value & operator = (const InformationTransferConfirmationIEs_Value &);
    int operator == (const InformationTransferConfirmationIEs_Value &) const;
    int operator != (const InformationTransferConfirmationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq202;

class OSS_PUBLIC __seqof195 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq202 component;

    __seqof195();
    __seqof195(const __seqof195 &);
    ~__seqof195();

    __seqof195 & operator = (const __seqof195 &);
    int operator == (const __seqof195 &) const;
    int operator != (const __seqof195 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof195 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof195 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof195 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC InformationTransferConfirmation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof195 protocolIEs;
    typedef __shared4 protocolExtensions;

    InformationTransferConfirmation();
    InformationTransferConfirmation(const InformationTransferConfirmation &);
    InformationTransferConfirmation(const protocolIEs &, const protocolExtensions &);
    InformationTransferConfirmation(const protocolIEs &);

    InformationTransferConfirmation & operator = (const InformationTransferConfirmation &);
    int operator == (const InformationTransferConfirmation &) const;
    int operator != (const InformationTransferConfirmation &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq202   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef InformationTransferConfirmationIEs_Value value;

    __seq202();
    __seq202(const __seq202 &);
    __seq202(id, criticality, const value &);

    __seq202 & operator = (const __seq202 &);
    int operator == (const __seq202 &) const;
    int operator != (const __seq202 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC InformationTransferFailureIEs_Value : public OssConstrainedOpenType
{
public:
    InformationTransferFailureIEs_Value();
    InformationTransferFailureIEs_Value(const InformationTransferFailureIEs_Value &);
    ~InformationTransferFailureIEs_Value();
    InformationTransferFailureIEs_Value & operator = (const InformationTransferFailureIEs_Value &);
    int operator == (const InformationTransferFailureIEs_Value &) const;
    int operator != (const InformationTransferFailureIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq204;

class OSS_PUBLIC __seqof197 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq204 component;

    __seqof197();
    __seqof197(const __seqof197 &);
    ~__seqof197();

    __seqof197 & operator = (const __seqof197 &);
    int operator == (const __seqof197 &) const;
    int operator != (const __seqof197 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof197 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof197 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof197 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC InformationTransferFailure   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof197 protocolIEs;
    typedef __shared4 protocolExtensions;

    InformationTransferFailure();
    InformationTransferFailure(const InformationTransferFailure &);
    InformationTransferFailure(const protocolIEs &, const protocolExtensions &);
    InformationTransferFailure(const protocolIEs &);

    InformationTransferFailure & operator = (const InformationTransferFailure &);
    int operator == (const InformationTransferFailure &) const;
    int operator != (const InformationTransferFailure &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq204   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef InformationTransferFailureIEs_Value value;

    __seq204();
    __seq204(const __seq204 &);
    __seq204(id, criticality, const value &);

    __seq204 & operator = (const __seq204 &);
    int operator == (const __seq204 &) const;
    int operator != (const __seq204 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC UESpecificInformationIndicationIEs_Value : public OssConstrainedOpenType
{
public:
    UESpecificInformationIndicationIEs_Value();
    UESpecificInformationIndicationIEs_Value(const UESpecificInformationIndicationIEs_Value &);
    ~UESpecificInformationIndicationIEs_Value();
    UESpecificInformationIndicationIEs_Value & operator = (const UESpecificInformationIndicationIEs_Value &);
    int operator == (const UESpecificInformationIndicationIEs_Value &) const;
    int operator != (const UESpecificInformationIndicationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    UESBI_Iu *get_UESBI_Iu();
    const UESBI_Iu *get_UESBI_Iu() const;
    void set_UESBI_Iu(const UESBI_Iu &);
    UESBI_Iu *release_UESBI_Iu();
    void set_UESBI_Iu(UESBI_Iu *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq206;

class OSS_PUBLIC __seqof199 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq206 component;

    __seqof199();
    __seqof199(const __seqof199 &);
    ~__seqof199();

    __seqof199 & operator = (const __seqof199 &);
    int operator == (const __seqof199 &) const;
    int operator != (const __seqof199 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof199 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof199 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof199 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC UESpecificInformationIndication   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof199 protocolIEs;
    typedef __shared4 protocolExtensions;

    UESpecificInformationIndication();
    UESpecificInformationIndication(const UESpecificInformationIndication &);
    UESpecificInformationIndication(const protocolIEs &, const protocolExtensions &);
    UESpecificInformationIndication(const protocolIEs &);

    UESpecificInformationIndication & operator = (const UESpecificInformationIndication &);
    int operator == (const UESpecificInformationIndication &) const;
    int operator != (const UESpecificInformationIndication &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq206   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef UESpecificInformationIndicationIEs_Value value;

    __seq206();
    __seq206(const __seq206 &);
    __seq206(id, criticality, const value &);

    __seq206 & operator = (const __seq206 &);
    int operator == (const __seq206 &) const;
    int operator != (const __seq206 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC DirectInformationTransferIEs_Value : public OssConstrainedOpenType
{
public:
    DirectInformationTransferIEs_Value();
    DirectInformationTransferIEs_Value(const DirectInformationTransferIEs_Value &);
    ~DirectInformationTransferIEs_Value();
    DirectInformationTransferIEs_Value & operator = (const DirectInformationTransferIEs_Value &);
    int operator == (const DirectInformationTransferIEs_Value &) const;
    int operator != (const DirectInformationTransferIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferType *get_InformationTransferType();
    const InformationTransferType *get_InformationTransferType() const;
    void set_InformationTransferType(const InformationTransferType &);
    InformationTransferType *release_InformationTransferType();
    void set_InformationTransferType(InformationTransferType *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq208;

class OSS_PUBLIC __seqof201 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq208 component;

    __seqof201();
    __seqof201(const __seqof201 &);
    ~__seqof201();

    __seqof201 & operator = (const __seqof201 &);
    int operator == (const __seqof201 &) const;
    int operator != (const __seqof201 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof201 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof201 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof201 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC DirectInformationTransfer   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof201 protocolIEs;
    typedef __shared4 protocolExtensions;

    DirectInformationTransfer();
    DirectInformationTransfer(const DirectInformationTransfer &);
    DirectInformationTransfer(const protocolIEs &, const protocolExtensions &);
    DirectInformationTransfer(const protocolIEs &);

    DirectInformationTransfer & operator = (const DirectInformationTransfer &);
    int operator == (const DirectInformationTransfer &) const;
    int operator != (const DirectInformationTransfer &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq208   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef DirectInformationTransferIEs_Value value;

    __seq208();
    __seq208(const __seq208 &);
    __seq208(id, criticality, const value &);

    __seq208 & operator = (const __seq208 &);
    int operator == (const __seq208 &) const;
    int operator != (const __seq208 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC UplinkInformationTransferIndicationIEs_Value : public OssConstrainedOpenType
{
public:
    UplinkInformationTransferIndicationIEs_Value();
    UplinkInformationTransferIndicationIEs_Value(const UplinkInformationTransferIndicationIEs_Value &);
    ~UplinkInformationTransferIndicationIEs_Value();
    UplinkInformationTransferIndicationIEs_Value & operator = (const UplinkInformationTransferIndicationIEs_Value &);
    int operator == (const UplinkInformationTransferIndicationIEs_Value &) const;
    int operator != (const UplinkInformationTransferIndicationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    InformationTransferType *get_InformationTransferType();
    const InformationTransferType *get_InformationTransferType() const;
    void set_InformationTransferType(const InformationTransferType &);
    InformationTransferType *release_InformationTransferType();
    void set_InformationTransferType(InformationTransferType *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalRNC_ID *get_GlobalRNC_ID();
    const GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_GlobalRNC_ID(const GlobalRNC_ID &);
    GlobalRNC_ID *release_GlobalRNC_ID();
    void set_GlobalRNC_ID(GlobalRNC_ID *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq210;

class OSS_PUBLIC __seqof203 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq210 component;

    __seqof203();
    __seqof203(const __seqof203 &);
    ~__seqof203();

    __seqof203 & operator = (const __seqof203 &);
    int operator == (const __seqof203 &) const;
    int operator != (const __seqof203 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof203 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof203 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof203 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC UplinkInformationTransferIndication   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof203 protocolIEs;
    typedef __shared4 protocolExtensions;

    UplinkInformationTransferIndication();
    UplinkInformationTransferIndication(const UplinkInformationTransferIndication &);
    UplinkInformationTransferIndication(const protocolIEs &, const protocolExtensions &);
    UplinkInformationTransferIndication(const protocolIEs &);

    UplinkInformationTransferIndication & operator = (const UplinkInformationTransferIndication &);
    int operator == (const UplinkInformationTransferIndication &) const;
    int operator != (const UplinkInformationTransferIndication &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq210   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef UplinkInformationTransferIndicationIEs_Value value;

    __seq210();
    __seq210(const __seq210 &);
    __seq210(id, criticality, const value &);

    __seq210 & operator = (const __seq210 &);
    int operator == (const __seq210 &) const;
    int operator != (const __seq210 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC UplinkInformationTransferConfirmationIEs_Value : public OssConstrainedOpenType
{
public:
    UplinkInformationTransferConfirmationIEs_Value();
    UplinkInformationTransferConfirmationIEs_Value(const UplinkInformationTransferConfirmationIEs_Value &);
    ~UplinkInformationTransferConfirmationIEs_Value();
    UplinkInformationTransferConfirmationIEs_Value & operator = (const UplinkInformationTransferConfirmationIEs_Value &);
    int operator == (const UplinkInformationTransferConfirmationIEs_Value &) const;
    int operator != (const UplinkInformationTransferConfirmationIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq212;

class OSS_PUBLIC __seqof205 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq212 component;

    __seqof205();
    __seqof205(const __seqof205 &);
    ~__seqof205();

    __seqof205 & operator = (const __seqof205 &);
    int operator == (const __seqof205 &) const;
    int operator != (const __seqof205 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof205 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof205 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof205 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC UplinkInformationTransferConfirmation   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof205 protocolIEs;
    typedef __shared4 protocolExtensions;

    UplinkInformationTransferConfirmation();
    UplinkInformationTransferConfirmation(const UplinkInformationTransferConfirmation &);
    UplinkInformationTransferConfirmation(const protocolIEs &, const protocolExtensions &);
    UplinkInformationTransferConfirmation(const protocolIEs &);

    UplinkInformationTransferConfirmation & operator = (const UplinkInformationTransferConfirmation &);
    int operator == (const UplinkInformationTransferConfirmation &) const;
    int operator != (const UplinkInformationTransferConfirmation &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq212   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef UplinkInformationTransferConfirmationIEs_Value value;

    __seq212();
    __seq212(const __seq212 &);
    __seq212(id, criticality, const value &);

    __seq212 & operator = (const __seq212 &);
    int operator == (const __seq212 &) const;
    int operator != (const __seq212 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

class OSS_PUBLIC UplinkInformationTransferFailureIEs_Value : public OssConstrainedOpenType
{
public:
    UplinkInformationTransferFailureIEs_Value();
    UplinkInformationTransferFailureIEs_Value(const UplinkInformationTransferFailureIEs_Value &);
    ~UplinkInformationTransferFailureIEs_Value();
    UplinkInformationTransferFailureIEs_Value & operator = (const UplinkInformationTransferFailureIEs_Value &);
    int operator == (const UplinkInformationTransferFailureIEs_Value &) const;
    int operator != (const UplinkInformationTransferFailureIEs_Value &) const;
    int set_decoded(PDU &);
    int grab_decoded(PDU &);
    int set_encoded(const EncodedBuffer &);
    int grab_encoded(EncodedBuffer &);
    int encode(OssControl &);

    InformationTransferID *get_InformationTransferID();
    const InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferID(const InformationTransferID &);
    InformationTransferID *release_InformationTransferID();
    void set_InformationTransferID(InformationTransferID *);

    CN_DomainIndicator *get_CN_DomainIndicator();
    const CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_CN_DomainIndicator(const CN_DomainIndicator &);
    CN_DomainIndicator *release_CN_DomainIndicator();
    void set_CN_DomainIndicator(CN_DomainIndicator *);

    GlobalCN_ID *get_GlobalCN_ID();
    const GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalCN_ID(const GlobalCN_ID &);
    GlobalCN_ID *release_GlobalCN_ID();
    void set_GlobalCN_ID(GlobalCN_ID *);

    Cause *get_Cause();
    const Cause *get_Cause() const;
    void set_Cause(const Cause &);
    Cause *release_Cause();
    void set_Cause(Cause *);

    CriticalityDiagnostics *get_CriticalityDiagnostics();
    const CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_CriticalityDiagnostics(const CriticalityDiagnostics &);
    CriticalityDiagnostics *release_CriticalityDiagnostics();
    void set_CriticalityDiagnostics(CriticalityDiagnostics *);
private:
    void cleanup_decoded();
};

class OSS_PUBLIC __seq214;

class OSS_PUBLIC __seqof207 : public OssList  /* SEQUENCE OF */
{
public:
    typedef __seq214 component;

    __seqof207();
    __seqof207(const __seqof207 &);
    ~__seqof207();

    __seqof207 & operator = (const __seqof207 &);
    int operator == (const __seqof207 &) const;
    int operator != (const __seqof207 &) const;

    component *at(OssIndex);
    const component *at(OssIndex) const;

    OssIndex prepend(const component & );
    OssIndex prepend(__seqof207 *);
    OssIndex insert_after(OssIndex, const component & );
    OssIndex insert_after(OssIndex, __seqof207 *);

    int remove_front();
    int remove_after(OssIndex);

    __seqof207 *extract_after(OssIndex, OssIndex);
};

class OSS_PUBLIC UplinkInformationTransferFailure   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef __seqof207 protocolIEs;
    typedef __shared4 protocolExtensions;

    UplinkInformationTransferFailure();
    UplinkInformationTransferFailure(const UplinkInformationTransferFailure &);
    UplinkInformationTransferFailure(const protocolIEs &, const protocolExtensions &);
    UplinkInformationTransferFailure(const protocolIEs &);

    UplinkInformationTransferFailure & operator = (const UplinkInformationTransferFailure &);
    int operator == (const UplinkInformationTransferFailure &) const;
    int operator != (const UplinkInformationTransferFailure &) const;

    protocolIEs & get_protocolIEs();
    const protocolIEs & get_protocolIEs() const;
    void set_protocolIEs(const protocolIEs &);

    protocolExtensions *get_protocolExtensions();
    const protocolExtensions *get_protocolExtensions() const;
    void set_protocolExtensions(const protocolExtensions &);
    int protocolExtensions_is_present() const;
    void omit_protocolExtensions();
private:
    OSS_UINT32 bit_mask;
    protocolIEs protocolIEs_field;
    protocolExtensions protocolExtensions_field;
};

class OSS_PUBLIC __seq214   /* SEQUENCE */
{
public:
    void * operator new(size_t size);
    void operator delete(void *ptr);

    typedef OSS_UINT32 id;
    typedef enum Criticality criticality;
    typedef UplinkInformationTransferFailureIEs_Value value;

    __seq214();
    __seq214(const __seq214 &);
    __seq214(id, criticality, const value &);

    __seq214 & operator = (const __seq214 &);
    int operator == (const __seq214 &) const;
    int operator != (const __seq214 &) const;

    id & get_id();
    id get_id() const;
    void set_id(id);

    criticality & get_criticality();
    criticality get_criticality() const;
    void set_criticality(criticality);

    value & get_value();
    const value & get_value() const;
    void set_value(const value &);
private:
    id id_field;
    criticality criticality_field;
    value value_field;
};

/* Universal PDU class */

class OSS_PUBLIC ranap_PDU : public UniversalPDU {
public:
    ranap_PDU();
    void set_RANAP_PDU(RANAP_PDU &);
    RANAP_PDU *get_RANAP_PDU() const;
    void set_AccuracyFulfilmentIndicator(AccuracyFulfilmentIndicator &);
    AccuracyFulfilmentIndicator *get_AccuracyFulfilmentIndicator() const;
    void set_Alt_RAB_Parameters(Alt_RAB_Parameters &);
    Alt_RAB_Parameters *get_Alt_RAB_Parameters() const;
    void set_AreaIdentity(AreaIdentity &);
    AreaIdentity *get_AreaIdentity() const;
    void set_Ass_RAB_Parameters(Ass_RAB_Parameters &);
    Ass_RAB_Parameters *get_Ass_RAB_Parameters() const;
    void set_BroadcastAssistanceDataDecipheringKeys(BroadcastAssistanceDataDecipheringKeys &);
    BroadcastAssistanceDataDecipheringKeys *get_BroadcastAssistanceDataDecipheringKeys() const;
    void set_Cause(Cause &);
    Cause *get_Cause() const;
    void set_CellLoadInformationGroup(CellLoadInformationGroup &);
    CellLoadInformationGroup *get_CellLoadInformationGroup() const;
    void set_ClientType(ClientType &);
    ClientType *get_ClientType() const;
    void set_CriticalityDiagnostics(CriticalityDiagnostics &);
    CriticalityDiagnostics *get_CriticalityDiagnostics() const;
    void set_MessageStructure(MessageStructure &);
    MessageStructure *get_MessageStructure() const;
    void set_ChosenEncryptionAlgorithm(ChosenEncryptionAlgorithm &);
    ChosenEncryptionAlgorithm *get_ChosenEncryptionAlgorithm() const;
    void set_ChosenIntegrityProtectionAlgorithm(ChosenIntegrityProtectionAlgorithm &);
    ChosenIntegrityProtectionAlgorithm *get_ChosenIntegrityProtectionAlgorithm() const;
    void set_ClassmarkInformation2(ClassmarkInformation2 &);
    ClassmarkInformation2 *get_ClassmarkInformation2() const;
    void set_ClassmarkInformation3(ClassmarkInformation3 &);
    ClassmarkInformation3 *get_ClassmarkInformation3() const;
    void set_CN_DomainIndicator(CN_DomainIndicator &);
    CN_DomainIndicator *get_CN_DomainIndicator() const;
    void set_DRX_CycleLengthCoefficient(DRX_CycleLengthCoefficient &);
    DRX_CycleLengthCoefficient *get_DRX_CycleLengthCoefficient() const;
    void set_EncryptionInformation(EncryptionInformation &);
    EncryptionInformation *get_EncryptionInformation() const;
    void set_GERAN_BSC_Container(GERAN_BSC_Container &);
    GERAN_BSC_Container *get_GERAN_BSC_Container() const;
    void set_GERAN_Classmark(GERAN_Classmark &);
    GERAN_Classmark *get_GERAN_Classmark() const;
    void set_GlobalCN_ID(GlobalCN_ID &);
    GlobalCN_ID *get_GlobalCN_ID() const;
    void set_GlobalRNC_ID(GlobalRNC_ID &);
    GlobalRNC_ID *get_GlobalRNC_ID() const;
    void set_HS_DSCH_MAC_d_Flow_ID(HS_DSCH_MAC_d_Flow_ID &);
    HS_DSCH_MAC_d_Flow_ID *get_HS_DSCH_MAC_d_Flow_ID() const;
    void set_InformationTransferID(InformationTransferID &);
    InformationTransferID *get_InformationTransferID() const;
    void set_InformationTransferType(InformationTransferType &);
    InformationTransferType *get_InformationTransferType() const;
    void set_IntegrityProtectionInformation(IntegrityProtectionInformation &);
    IntegrityProtectionInformation *get_IntegrityProtectionInformation() const;
    void set_InterSystemInformationTransferType(InterSystemInformationTransferType &);
    InterSystemInformationTransferType *get_InterSystemInformationTransferType() const;
    void set_InterSystemInformation_TransparentContainer(InterSystemInformation_TransparentContainer &);
    InterSystemInformation_TransparentContainer *get_InterSystemInformation_TransparentContainer() const;
    void set_IuSignallingConnectionIdentifier(IuSignallingConnectionIdentifier &);
    IuSignallingConnectionIdentifier *get_IuSignallingConnectionIdentifier() const;
    void set_IuTransportAssociation(IuTransportAssociation &);
    IuTransportAssociation *get_IuTransportAssociation() const;
    void set_KeyStatus(KeyStatus &);
    KeyStatus *get_KeyStatus() const;
    void set_LAI(LAI &);
    LAI *get_LAI() const;
    void set_LastKnownServiceArea(LastKnownServiceArea &);
    LastKnownServiceArea *get_LastKnownServiceArea() const;
    void set_LocationRelatedDataRequestType(LocationRelatedDataRequestType &);
    LocationRelatedDataRequestType *get_LocationRelatedDataRequestType() const;
    void set_LocationRelatedDataRequestTypeSpecificToGERANIuMode(LocationRelatedDataRequestTypeSpecificToGERANIuMode &);
    LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_LocationRelatedDataRequestTypeSpecificToGERANIuMode() const;
    void set_L3_Information(L3_Information &);
    L3_Information *get_L3_Information() const;
    void set_NAS_PDU(NAS_PDU &);
    NAS_PDU *get_NAS_PDU() const;
    void set_NewBSS_To_OldBSS_Information(NewBSS_To_OldBSS_Information &);
    NewBSS_To_OldBSS_Information *get_NewBSS_To_OldBSS_Information() const;
    void set_NonSearchingIndication(NonSearchingIndication &);
    NonSearchingIndication *get_NonSearchingIndication() const;
    void set_NumberOfSteps(NumberOfSteps &);
    NumberOfSteps *get_NumberOfSteps() const;
    void set_OldBSS_ToNewBSS_Information(OldBSS_ToNewBSS_Information &);
    OldBSS_ToNewBSS_Information *get_OldBSS_ToNewBSS_Information() const;
    void set_OMC_ID(OMC_ID &);
    OMC_ID *get_OMC_ID() const;
    void set_PagingAreaID(PagingAreaID &);
    PagingAreaID *get_PagingAreaID() const;
    void set_PagingCause(PagingCause &);
    PagingCause *get_PagingCause() const;
    void set_PermanentNAS_UE_ID(PermanentNAS_UE_ID &);
    PermanentNAS_UE_ID *get_PermanentNAS_UE_ID() const;
    void set_PositioningPriority(PositioningPriority &);
    PositioningPriority *get_PositioningPriority() const;
    void set_PositionData(PositionData &);
    PositionData *get_PositionData() const;
    void set_PositionDataSpecificToGERANIuMode(PositionDataSpecificToGERANIuMode &);
    PositionDataSpecificToGERANIuMode *get_PositionDataSpecificToGERANIuMode() const;
    void set_ProvidedData(ProvidedData &);
    ProvidedData *get_ProvidedData() const;
    void set_RAC(RAC &);
    RAC *get_RAC() const;
    void set_RateControlAllowed(RateControlAllowed &);
    RateControlAllowed *get_RateControlAllowed() const;
    void set_RelocationType(RelocationType &);
    RelocationType *get_RelocationType() const;
    void set_RequestType(RequestType &);
    RequestType *get_RequestType() const;
    void set_ResponseTime(ResponseTime &);
    ResponseTime *get_ResponseTime() const;
    void set_RRC_Container(RRC_Container &);
    RRC_Container *get_RRC_Container() const;
    void set_SAI(SAI &);
    SAI *get_SAI() const;
    void set_SAPI(SAPI &);
    SAPI *get_SAPI() const;
    void set_SignallingIndication(SignallingIndication &);
    SignallingIndication *get_SignallingIndication() const;
    void set_SNA_Access_Information(SNA_Access_Information &);
    SNA_Access_Information *get_SNA_Access_Information() const;
    void set_SourceID(SourceID &);
    SourceID *get_SourceID() const;
    void set_SourceRNC_ToTargetRNC_TransparentContainer(SourceRNC_ToTargetRNC_TransparentContainer &);
    SourceRNC_ToTargetRNC_TransparentContainer *get_SourceRNC_ToTargetRNC_TransparentContainer() const;
    void set_SRB_TrCH_Mapping(SRB_TrCH_Mapping &);
    SRB_TrCH_Mapping *get_SRB_TrCH_Mapping() const;
    void set_TargetID(TargetID &);
    TargetID *get_TargetID() const;
    void set_TargetRNC_ToSourceRNC_TransparentContainer(TargetRNC_ToSourceRNC_TransparentContainer &);
    TargetRNC_ToSourceRNC_TransparentContainer *get_TargetRNC_ToSourceRNC_TransparentContainer() const;
    void set_TemporaryUE_ID(TemporaryUE_ID &);
    TemporaryUE_ID *get_TemporaryUE_ID() const;
    void set_TracePropagationParameters(TracePropagationParameters &);
    TracePropagationParameters *get_TracePropagationParameters() const;
    void set_TraceRecordingSessionInformation(TraceRecordingSessionInformation &);
    TraceRecordingSessionInformation *get_TraceRecordingSessionInformation() const;
    void set_TraceReference(TraceReference &);
    TraceReference *get_TraceReference() const;
    void set_TraceType(TraceType &);
    TraceType *get_TraceType() const;
    void set_TransportLayerAddress(TransportLayerAddress &);
    TransportLayerAddress *get_TransportLayerAddress() const;
    void set_TriggerID(TriggerID &);
    TriggerID *get_TriggerID() const;
    void set_TypeOfError(TypeOfError &);
    TypeOfError *get_TypeOfError() const;
    void set_UE_ID(UE_ID &);
    UE_ID *get_UE_ID() const;
    void set_UESBI_Iu(UESBI_Iu &);
    UESBI_Iu *get_UESBI_Iu() const;
    void set_VerticalAccuracyCode(VerticalAccuracyCode &);
    VerticalAccuracyCode *get_VerticalAccuracyCode() const;
    void set_Iu_ReleaseCommand(Iu_ReleaseCommand &);
    Iu_ReleaseCommand *get_Iu_ReleaseCommand() const;
    void set_Iu_ReleaseComplete(Iu_ReleaseComplete &);
    Iu_ReleaseComplete *get_Iu_ReleaseComplete() const;
    void set_RAB_DataVolumeReportList(RAB_DataVolumeReportList &);
    RAB_DataVolumeReportList *get_RAB_DataVolumeReportList() const;
    void set_RAB_DataVolumeReportItem(RAB_DataVolumeReportItem &);
    RAB_DataVolumeReportItem *get_RAB_DataVolumeReportItem() const;
    void set_RAB_ReleasedList_IuRelComp(RAB_ReleasedList_IuRelComp &);
    RAB_ReleasedList_IuRelComp *get_RAB_ReleasedList_IuRelComp() const;
    void set_RAB_ReleasedItem_IuRelComp(RAB_ReleasedItem_IuRelComp &);
    RAB_ReleasedItem_IuRelComp *get_RAB_ReleasedItem_IuRelComp() const;
    void set_RelocationRequired(RelocationRequired &);
    RelocationRequired *get_RelocationRequired() const;
    void set_RelocationCommand(RelocationCommand &);
    RelocationCommand *get_RelocationCommand() const;
    void set_RAB_RelocationReleaseList(RAB_RelocationReleaseList &);
    RAB_RelocationReleaseList *get_RAB_RelocationReleaseList() const;
    void set_RAB_RelocationReleaseItem(RAB_RelocationReleaseItem &);
    RAB_RelocationReleaseItem *get_RAB_RelocationReleaseItem() const;
    void set_RAB_DataForwardingList(RAB_DataForwardingList &);
    RAB_DataForwardingList *get_RAB_DataForwardingList() const;
    void set_RAB_DataForwardingItem(RAB_DataForwardingItem &);
    RAB_DataForwardingItem *get_RAB_DataForwardingItem() const;
    void set_RelocationPreparationFailure(RelocationPreparationFailure &);
    RelocationPreparationFailure *get_RelocationPreparationFailure() const;
    void set_RelocationRequest(RelocationRequest &);
    RelocationRequest *get_RelocationRequest() const;
    void set_RAB_SetupList_RelocReq(RAB_SetupList_RelocReq &);
    RAB_SetupList_RelocReq *get_RAB_SetupList_RelocReq() const;
    void set_RAB_SetupItem_RelocReq(RAB_SetupItem_RelocReq &);
    RAB_SetupItem_RelocReq *get_RAB_SetupItem_RelocReq() const;
    void set_RelocationRequestAcknowledge(RelocationRequestAcknowledge &);
    RelocationRequestAcknowledge *get_RelocationRequestAcknowledge() const;
    void set_RAB_SetupList_RelocReqAck(RAB_SetupList_RelocReqAck &);
    RAB_SetupList_RelocReqAck *get_RAB_SetupList_RelocReqAck() const;
    void set_RAB_SetupItem_RelocReqAck(RAB_SetupItem_RelocReqAck &);
    RAB_SetupItem_RelocReqAck *get_RAB_SetupItem_RelocReqAck() const;
    void set_RAB_FailedList(RAB_FailedList &);
    RAB_FailedList *get_RAB_FailedList() const;
    void set_RAB_FailedItem(RAB_FailedItem &);
    RAB_FailedItem *get_RAB_FailedItem() const;
    void set_RelocationFailure(RelocationFailure &);
    RelocationFailure *get_RelocationFailure() const;
    void set_RelocationCancel(RelocationCancel &);
    RelocationCancel *get_RelocationCancel() const;
    void set_RelocationCancelAcknowledge(RelocationCancelAcknowledge &);
    RelocationCancelAcknowledge *get_RelocationCancelAcknowledge() const;
    void set_SRNS_ContextRequest(SRNS_ContextRequest &);
    SRNS_ContextRequest *get_SRNS_ContextRequest() const;
    void set_RAB_DataForwardingList_SRNS_CtxReq(RAB_DataForwardingList_SRNS_CtxReq &);
    RAB_DataForwardingList_SRNS_CtxReq *get_RAB_DataForwardingList_SRNS_CtxReq() const;
    void set_RAB_DataForwardingItem_SRNS_CtxReq(RAB_DataForwardingItem_SRNS_CtxReq &);
    RAB_DataForwardingItem_SRNS_CtxReq *get_RAB_DataForwardingItem_SRNS_CtxReq() const;
    void set_SRNS_ContextResponse(SRNS_ContextResponse &);
    SRNS_ContextResponse *get_SRNS_ContextResponse() const;
    void set_RAB_ContextList(RAB_ContextList &);
    RAB_ContextList *get_RAB_ContextList() const;
    void set_RAB_ContextItem(RAB_ContextItem &);
    RAB_ContextItem *get_RAB_ContextItem() const;
    void set_RAB_ContextFailedtoTransferList(RAB_ContextFailedtoTransferList &);
    RAB_ContextFailedtoTransferList *get_RAB_ContextFailedtoTransferList() const;
    void set_RABs_ContextFailedtoTransferItem(RABs_ContextFailedtoTransferItem &);
    RABs_ContextFailedtoTransferItem *get_RABs_ContextFailedtoTransferItem() const;
    void set_SecurityModeCommand(SecurityModeCommand &);
    SecurityModeCommand *get_SecurityModeCommand() const;
    void set_SecurityModeComplete(SecurityModeComplete &);
    SecurityModeComplete *get_SecurityModeComplete() const;
    void set_SecurityModeReject(SecurityModeReject &);
    SecurityModeReject *get_SecurityModeReject() const;
    void set_DataVolumeReportRequest(DataVolumeReportRequest &);
    DataVolumeReportRequest *get_DataVolumeReportRequest() const;
    void set_RAB_DataVolumeReportRequestList(RAB_DataVolumeReportRequestList &);
    RAB_DataVolumeReportRequestList *get_RAB_DataVolumeReportRequestList() const;
    void set_RAB_DataVolumeReportRequestItem(RAB_DataVolumeReportRequestItem &);
    RAB_DataVolumeReportRequestItem *get_RAB_DataVolumeReportRequestItem() const;
    void set_DataVolumeReport(DataVolumeReport &);
    DataVolumeReport *get_DataVolumeReport() const;
    void set_RAB_FailedtoReportList(RAB_FailedtoReportList &);
    RAB_FailedtoReportList *get_RAB_FailedtoReportList() const;
    void set_RABs_failed_to_reportItem(RABs_failed_to_reportItem &);
    RABs_failed_to_reportItem *get_RABs_failed_to_reportItem() const;
    void set_Reset(Reset &);
    Reset *get_Reset() const;
    void set_ResetAcknowledge(ResetAcknowledge &);
    ResetAcknowledge *get_ResetAcknowledge() const;
    void set_ResetResource(ResetResource &);
    ResetResource *get_ResetResource() const;
    void set_ResetResourceList(ResetResourceList &);
    ResetResourceList *get_ResetResourceList() const;
    void set_ResetResourceItem(ResetResourceItem &);
    ResetResourceItem *get_ResetResourceItem() const;
    void set_ResetResourceAcknowledge(ResetResourceAcknowledge &);
    ResetResourceAcknowledge *get_ResetResourceAcknowledge() const;
    void set_ResetResourceAckList(ResetResourceAckList &);
    ResetResourceAckList *get_ResetResourceAckList() const;
    void set_ResetResourceAckItem(ResetResourceAckItem &);
    ResetResourceAckItem *get_ResetResourceAckItem() const;
    void set_RAB_ReleaseRequest(RAB_ReleaseRequest &);
    RAB_ReleaseRequest *get_RAB_ReleaseRequest() const;
    void set_RAB_ReleaseList(RAB_ReleaseList &);
    RAB_ReleaseList *get_RAB_ReleaseList() const;
    void set_RAB_ReleaseItem(RAB_ReleaseItem &);
    RAB_ReleaseItem *get_RAB_ReleaseItem() const;
    void set_Iu_ReleaseRequest(Iu_ReleaseRequest &);
    Iu_ReleaseRequest *get_Iu_ReleaseRequest() const;
    void set_RelocationDetect(RelocationDetect &);
    RelocationDetect *get_RelocationDetect() const;
    void set_RelocationComplete(RelocationComplete &);
    RelocationComplete *get_RelocationComplete() const;
    void set_Paging(Paging &);
    Paging *get_Paging() const;
    void set_CommonID(CommonID &);
    CommonID *get_CommonID() const;
    void set_CN_InvokeTrace(CN_InvokeTrace &);
    CN_InvokeTrace *get_CN_InvokeTrace() const;
    void set_CN_DeactivateTrace(CN_DeactivateTrace &);
    CN_DeactivateTrace *get_CN_DeactivateTrace() const;
    void set_LocationReportingControl(LocationReportingControl &);
    LocationReportingControl *get_LocationReportingControl() const;
    void set_LocationReport(LocationReport &);
    LocationReport *get_LocationReport() const;
    void set_InitialUE_Message(InitialUE_Message &);
    InitialUE_Message *get_InitialUE_Message() const;
    void set_DirectTransfer(DirectTransfer &);
    DirectTransfer *get_DirectTransfer() const;
    void set_Overload(Overload &);
    Overload *get_Overload() const;
    void set_ErrorIndication(ErrorIndication &);
    ErrorIndication *get_ErrorIndication() const;
    void set_SRNS_DataForwardCommand(SRNS_DataForwardCommand &);
    SRNS_DataForwardCommand *get_SRNS_DataForwardCommand() const;
    void set_ForwardSRNS_Context(ForwardSRNS_Context &);
    ForwardSRNS_Context *get_ForwardSRNS_Context() const;
    void set_RAB_AssignmentRequest(RAB_AssignmentRequest &);
    RAB_AssignmentRequest *get_RAB_AssignmentRequest() const;
    void set_RAB_SetupOrModifyList(RAB_SetupOrModifyList &);
    RAB_SetupOrModifyList *get_RAB_SetupOrModifyList() const;
    void set_RAB_SetupOrModifyItemFirst(RAB_SetupOrModifyItemFirst &);
    RAB_SetupOrModifyItemFirst *get_RAB_SetupOrModifyItemFirst() const;
    void set_RAB_SetupOrModifyItemSecond(RAB_SetupOrModifyItemSecond &);
    RAB_SetupOrModifyItemSecond *get_RAB_SetupOrModifyItemSecond() const;
    void set_RAB_AssignmentResponse(RAB_AssignmentResponse &);
    RAB_AssignmentResponse *get_RAB_AssignmentResponse() const;
    void set_RAB_SetupOrModifiedList(RAB_SetupOrModifiedList &);
    RAB_SetupOrModifiedList *get_RAB_SetupOrModifiedList() const;
    void set_RAB_SetupOrModifiedItem(RAB_SetupOrModifiedItem &);
    RAB_SetupOrModifiedItem *get_RAB_SetupOrModifiedItem() const;
    void set_RAB_ReleasedList(RAB_ReleasedList &);
    RAB_ReleasedList *get_RAB_ReleasedList() const;
    void set_RAB_ReleasedItem(RAB_ReleasedItem &);
    RAB_ReleasedItem *get_RAB_ReleasedItem() const;
    void set_RAB_QueuedList(RAB_QueuedList &);
    RAB_QueuedList *get_RAB_QueuedList() const;
    void set_RAB_QueuedItem(RAB_QueuedItem &);
    RAB_QueuedItem *get_RAB_QueuedItem() const;
    void set_RAB_ReleaseFailedList(RAB_ReleaseFailedList &);
    RAB_ReleaseFailedList *get_RAB_ReleaseFailedList() const;
    void set_GERAN_Iumode_RAB_FailedList_RABAssgntResponse(GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_GERAN_Iumode_RAB_FailedList_RABAssgntResponse() const;
    void set_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item() const;
    void set_PrivateMessage(PrivateMessage &);
    PrivateMessage *get_PrivateMessage() const;
    void set_RANAP_RelocationInformation(RANAP_RelocationInformation &);
    RANAP_RelocationInformation *get_RANAP_RelocationInformation() const;
    void set_DirectTransferInformationList_RANAP_RelocInf(DirectTransferInformationList_RANAP_RelocInf &);
    DirectTransferInformationList_RANAP_RelocInf *get_DirectTransferInformationList_RANAP_RelocInf() const;
    void set_DirectTransferInformationItem_RANAP_RelocInf(DirectTransferInformationItem_RANAP_RelocInf &);
    DirectTransferInformationItem_RANAP_RelocInf *get_DirectTransferInformationItem_RANAP_RelocInf() const;
    void set_RAB_ContextList_RANAP_RelocInf(RAB_ContextList_RANAP_RelocInf &);
    RAB_ContextList_RANAP_RelocInf *get_RAB_ContextList_RANAP_RelocInf() const;
    void set_RAB_ContextItem_RANAP_RelocInf(RAB_ContextItem_RANAP_RelocInf &);
    RAB_ContextItem_RANAP_RelocInf *get_RAB_ContextItem_RANAP_RelocInf() const;
    void set_RAB_ModifyRequest(RAB_ModifyRequest &);
    RAB_ModifyRequest *get_RAB_ModifyRequest() const;
    void set_RAB_ModifyList(RAB_ModifyList &);
    RAB_ModifyList *get_RAB_ModifyList() const;
    void set_RAB_ModifyItem(RAB_ModifyItem &);
    RAB_ModifyItem *get_RAB_ModifyItem() const;
    void set_LocationRelatedDataRequest(LocationRelatedDataRequest &);
    LocationRelatedDataRequest *get_LocationRelatedDataRequest() const;
    void set_LocationRelatedDataResponse(LocationRelatedDataResponse &);
    LocationRelatedDataResponse *get_LocationRelatedDataResponse() const;
    void set_LocationRelatedDataFailure(LocationRelatedDataFailure &);
    LocationRelatedDataFailure *get_LocationRelatedDataFailure() const;
    void set_InformationTransferIndication(InformationTransferIndication &);
    InformationTransferIndication *get_InformationTransferIndication() const;
    void set_InformationTransferConfirmation(InformationTransferConfirmation &);
    InformationTransferConfirmation *get_InformationTransferConfirmation() const;
    void set_InformationTransferFailure(InformationTransferFailure &);
    InformationTransferFailure *get_InformationTransferFailure() const;
    void set_UESpecificInformationIndication(UESpecificInformationIndication &);
    UESpecificInformationIndication *get_UESpecificInformationIndication() const;
    void set_DirectInformationTransfer(DirectInformationTransfer &);
    DirectInformationTransfer *get_DirectInformationTransfer() const;
    void set_UplinkInformationTransferIndication(UplinkInformationTransferIndication &);
    UplinkInformationTransferIndication *get_UplinkInformationTransferIndication() const;
    void set_UplinkInformationTransferConfirmation(UplinkInformationTransferConfirmation &);
    UplinkInformationTransferConfirmation *get_UplinkInformationTransferConfirmation() const;
    void set_UplinkInformationTransferFailure(UplinkInformationTransferFailure &);
    UplinkInformationTransferFailure *get_UplinkInformationTransferFailure() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_RANAP_PDU(const RANAP_PDU &);
    const RANAP_PDU *get_const_RANAP_PDU() const;
    void set_const_AccuracyFulfilmentIndicator(const AccuracyFulfilmentIndicator &);
    const AccuracyFulfilmentIndicator *get_const_AccuracyFulfilmentIndicator() const;
    void set_const_Alt_RAB_Parameters(const Alt_RAB_Parameters &);
    const Alt_RAB_Parameters *get_const_Alt_RAB_Parameters() const;
    void set_const_AreaIdentity(const AreaIdentity &);
    const AreaIdentity *get_const_AreaIdentity() const;
    void set_const_Ass_RAB_Parameters(const Ass_RAB_Parameters &);
    const Ass_RAB_Parameters *get_const_Ass_RAB_Parameters() const;
    void set_const_BroadcastAssistanceDataDecipheringKeys(const BroadcastAssistanceDataDecipheringKeys &);
    const BroadcastAssistanceDataDecipheringKeys *get_const_BroadcastAssistanceDataDecipheringKeys() const;
    void set_const_Cause(const Cause &);
    const Cause *get_const_Cause() const;
    void set_const_CellLoadInformationGroup(const CellLoadInformationGroup &);
    const CellLoadInformationGroup *get_const_CellLoadInformationGroup() const;
    void set_const_ClientType(const ClientType &);
    const ClientType *get_const_ClientType() const;
    void set_const_CriticalityDiagnostics(const CriticalityDiagnostics &);
    const CriticalityDiagnostics *get_const_CriticalityDiagnostics() const;
    void set_const_MessageStructure(const MessageStructure &);
    const MessageStructure *get_const_MessageStructure() const;
    void set_const_ChosenEncryptionAlgorithm(const ChosenEncryptionAlgorithm &);
    const ChosenEncryptionAlgorithm *get_const_ChosenEncryptionAlgorithm() const;
    void set_const_ChosenIntegrityProtectionAlgorithm(const ChosenIntegrityProtectionAlgorithm &);
    const ChosenIntegrityProtectionAlgorithm *get_const_ChosenIntegrityProtectionAlgorithm() const;
    void set_const_ClassmarkInformation2(const ClassmarkInformation2 &);
    const ClassmarkInformation2 *get_const_ClassmarkInformation2() const;
    void set_const_ClassmarkInformation3(const ClassmarkInformation3 &);
    const ClassmarkInformation3 *get_const_ClassmarkInformation3() const;
    void set_const_CN_DomainIndicator(const CN_DomainIndicator &);
    const CN_DomainIndicator *get_const_CN_DomainIndicator() const;
    void set_const_DRX_CycleLengthCoefficient(const DRX_CycleLengthCoefficient &);
    const DRX_CycleLengthCoefficient *get_const_DRX_CycleLengthCoefficient() const;
    void set_const_EncryptionInformation(const EncryptionInformation &);
    const EncryptionInformation *get_const_EncryptionInformation() const;
    void set_const_GERAN_BSC_Container(const GERAN_BSC_Container &);
    const GERAN_BSC_Container *get_const_GERAN_BSC_Container() const;
    void set_const_GERAN_Classmark(const GERAN_Classmark &);
    const GERAN_Classmark *get_const_GERAN_Classmark() const;
    void set_const_GlobalCN_ID(const GlobalCN_ID &);
    const GlobalCN_ID *get_const_GlobalCN_ID() const;
    void set_const_GlobalRNC_ID(const GlobalRNC_ID &);
    const GlobalRNC_ID *get_const_GlobalRNC_ID() const;
    void set_const_HS_DSCH_MAC_d_Flow_ID(const HS_DSCH_MAC_d_Flow_ID &);
    const HS_DSCH_MAC_d_Flow_ID *get_const_HS_DSCH_MAC_d_Flow_ID() const;
    void set_const_InformationTransferID(const InformationTransferID &);
    const InformationTransferID *get_const_InformationTransferID() const;
    void set_const_InformationTransferType(const InformationTransferType &);
    const InformationTransferType *get_const_InformationTransferType() const;
    void set_const_IntegrityProtectionInformation(const IntegrityProtectionInformation &);
    const IntegrityProtectionInformation *get_const_IntegrityProtectionInformation() const;
    void set_const_InterSystemInformationTransferType(const InterSystemInformationTransferType &);
    const InterSystemInformationTransferType *get_const_InterSystemInformationTransferType() const;
    void set_const_InterSystemInformation_TransparentContainer(const InterSystemInformation_TransparentContainer &);
    const InterSystemInformation_TransparentContainer *get_const_InterSystemInformation_TransparentContainer() const;
    void set_const_IuSignallingConnectionIdentifier(const IuSignallingConnectionIdentifier &);
    const IuSignallingConnectionIdentifier *get_const_IuSignallingConnectionIdentifier() const;
    void set_const_IuTransportAssociation(const IuTransportAssociation &);
    const IuTransportAssociation *get_const_IuTransportAssociation() const;
    void set_const_KeyStatus(const KeyStatus &);
    const KeyStatus *get_const_KeyStatus() const;
    void set_const_LAI(const LAI &);
    const LAI *get_const_LAI() const;
    void set_const_LastKnownServiceArea(const LastKnownServiceArea &);
    const LastKnownServiceArea *get_const_LastKnownServiceArea() const;
    void set_const_LocationRelatedDataRequestType(const LocationRelatedDataRequestType &);
    const LocationRelatedDataRequestType *get_const_LocationRelatedDataRequestType() const;
    void set_const_LocationRelatedDataRequestTypeSpecificToGERANIuMode(const LocationRelatedDataRequestTypeSpecificToGERANIuMode &);
    const LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_const_LocationRelatedDataRequestTypeSpecificToGERANIuMode() const;
    void set_const_L3_Information(const L3_Information &);
    const L3_Information *get_const_L3_Information() const;
    void set_const_NAS_PDU(const NAS_PDU &);
    const NAS_PDU *get_const_NAS_PDU() const;
    void set_const_NewBSS_To_OldBSS_Information(const NewBSS_To_OldBSS_Information &);
    const NewBSS_To_OldBSS_Information *get_const_NewBSS_To_OldBSS_Information() const;
    void set_const_NonSearchingIndication(const NonSearchingIndication &);
    const NonSearchingIndication *get_const_NonSearchingIndication() const;
    void set_const_NumberOfSteps(const NumberOfSteps &);
    const NumberOfSteps *get_const_NumberOfSteps() const;
    void set_const_OldBSS_ToNewBSS_Information(const OldBSS_ToNewBSS_Information &);
    const OldBSS_ToNewBSS_Information *get_const_OldBSS_ToNewBSS_Information() const;
    void set_const_OMC_ID(const OMC_ID &);
    const OMC_ID *get_const_OMC_ID() const;
    void set_const_PagingAreaID(const PagingAreaID &);
    const PagingAreaID *get_const_PagingAreaID() const;
    void set_const_PagingCause(const PagingCause &);
    const PagingCause *get_const_PagingCause() const;
    void set_const_PermanentNAS_UE_ID(const PermanentNAS_UE_ID &);
    const PermanentNAS_UE_ID *get_const_PermanentNAS_UE_ID() const;
    void set_const_PositioningPriority(const PositioningPriority &);
    const PositioningPriority *get_const_PositioningPriority() const;
    void set_const_PositionData(const PositionData &);
    const PositionData *get_const_PositionData() const;
    void set_const_PositionDataSpecificToGERANIuMode(const PositionDataSpecificToGERANIuMode &);
    const PositionDataSpecificToGERANIuMode *get_const_PositionDataSpecificToGERANIuMode() const;
    void set_const_ProvidedData(const ProvidedData &);
    const ProvidedData *get_const_ProvidedData() const;
    void set_const_RAC(const RAC &);
    const RAC *get_const_RAC() const;
    void set_const_RateControlAllowed(const RateControlAllowed &);
    const RateControlAllowed *get_const_RateControlAllowed() const;
    void set_const_RelocationType(const RelocationType &);
    const RelocationType *get_const_RelocationType() const;
    void set_const_RequestType(const RequestType &);
    const RequestType *get_const_RequestType() const;
    void set_const_ResponseTime(const ResponseTime &);
    const ResponseTime *get_const_ResponseTime() const;
    void set_const_RRC_Container(const RRC_Container &);
    const RRC_Container *get_const_RRC_Container() const;
    void set_const_SAI(const SAI &);
    const SAI *get_const_SAI() const;
    void set_const_SAPI(const SAPI &);
    const SAPI *get_const_SAPI() const;
    void set_const_SignallingIndication(const SignallingIndication &);
    const SignallingIndication *get_const_SignallingIndication() const;
    void set_const_SNA_Access_Information(const SNA_Access_Information &);
    const SNA_Access_Information *get_const_SNA_Access_Information() const;
    void set_const_SourceID(const SourceID &);
    const SourceID *get_const_SourceID() const;
    void set_const_SourceRNC_ToTargetRNC_TransparentContainer(const SourceRNC_ToTargetRNC_TransparentContainer &);
    const SourceRNC_ToTargetRNC_TransparentContainer *get_const_SourceRNC_ToTargetRNC_TransparentContainer() const;
    void set_const_SRB_TrCH_Mapping(const SRB_TrCH_Mapping &);
    const SRB_TrCH_Mapping *get_const_SRB_TrCH_Mapping() const;
    void set_const_TargetID(const TargetID &);
    const TargetID *get_const_TargetID() const;
    void set_const_TargetRNC_ToSourceRNC_TransparentContainer(const TargetRNC_ToSourceRNC_TransparentContainer &);
    const TargetRNC_ToSourceRNC_TransparentContainer *get_const_TargetRNC_ToSourceRNC_TransparentContainer() const;
    void set_const_TemporaryUE_ID(const TemporaryUE_ID &);
    const TemporaryUE_ID *get_const_TemporaryUE_ID() const;
    void set_const_TracePropagationParameters(const TracePropagationParameters &);
    const TracePropagationParameters *get_const_TracePropagationParameters() const;
    void set_const_TraceRecordingSessionInformation(const TraceRecordingSessionInformation &);
    const TraceRecordingSessionInformation *get_const_TraceRecordingSessionInformation() const;
    void set_const_TraceReference(const TraceReference &);
    const TraceReference *get_const_TraceReference() const;
    void set_const_TraceType(const TraceType &);
    const TraceType *get_const_TraceType() const;
    void set_const_TransportLayerAddress(const TransportLayerAddress &);
    const TransportLayerAddress *get_const_TransportLayerAddress() const;
    void set_const_TriggerID(const TriggerID &);
    const TriggerID *get_const_TriggerID() const;
    void set_const_TypeOfError(const TypeOfError &);
    const TypeOfError *get_const_TypeOfError() const;
    void set_const_UE_ID(const UE_ID &);
    const UE_ID *get_const_UE_ID() const;
    void set_const_UESBI_Iu(const UESBI_Iu &);
    const UESBI_Iu *get_const_UESBI_Iu() const;
    void set_const_VerticalAccuracyCode(const VerticalAccuracyCode &);
    const VerticalAccuracyCode *get_const_VerticalAccuracyCode() const;
    void set_const_Iu_ReleaseCommand(const Iu_ReleaseCommand &);
    const Iu_ReleaseCommand *get_const_Iu_ReleaseCommand() const;
    void set_const_Iu_ReleaseComplete(const Iu_ReleaseComplete &);
    const Iu_ReleaseComplete *get_const_Iu_ReleaseComplete() const;
    void set_const_RAB_DataVolumeReportList(const RAB_DataVolumeReportList &);
    const RAB_DataVolumeReportList *get_const_RAB_DataVolumeReportList() const;
    void set_const_RAB_DataVolumeReportItem(const RAB_DataVolumeReportItem &);
    const RAB_DataVolumeReportItem *get_const_RAB_DataVolumeReportItem() const;
    void set_const_RAB_ReleasedList_IuRelComp(const RAB_ReleasedList_IuRelComp &);
    const RAB_ReleasedList_IuRelComp *get_const_RAB_ReleasedList_IuRelComp() const;
    void set_const_RAB_ReleasedItem_IuRelComp(const RAB_ReleasedItem_IuRelComp &);
    const RAB_ReleasedItem_IuRelComp *get_const_RAB_ReleasedItem_IuRelComp() const;
    void set_const_RelocationRequired(const RelocationRequired &);
    const RelocationRequired *get_const_RelocationRequired() const;
    void set_const_RelocationCommand(const RelocationCommand &);
    const RelocationCommand *get_const_RelocationCommand() const;
    void set_const_RAB_RelocationReleaseList(const RAB_RelocationReleaseList &);
    const RAB_RelocationReleaseList *get_const_RAB_RelocationReleaseList() const;
    void set_const_RAB_RelocationReleaseItem(const RAB_RelocationReleaseItem &);
    const RAB_RelocationReleaseItem *get_const_RAB_RelocationReleaseItem() const;
    void set_const_RAB_DataForwardingList(const RAB_DataForwardingList &);
    const RAB_DataForwardingList *get_const_RAB_DataForwardingList() const;
    void set_const_RAB_DataForwardingItem(const RAB_DataForwardingItem &);
    const RAB_DataForwardingItem *get_const_RAB_DataForwardingItem() const;
    void set_const_RelocationPreparationFailure(const RelocationPreparationFailure &);
    const RelocationPreparationFailure *get_const_RelocationPreparationFailure() const;
    void set_const_RelocationRequest(const RelocationRequest &);
    const RelocationRequest *get_const_RelocationRequest() const;
    void set_const_RAB_SetupList_RelocReq(const RAB_SetupList_RelocReq &);
    const RAB_SetupList_RelocReq *get_const_RAB_SetupList_RelocReq() const;
    void set_const_RAB_SetupItem_RelocReq(const RAB_SetupItem_RelocReq &);
    const RAB_SetupItem_RelocReq *get_const_RAB_SetupItem_RelocReq() const;
    void set_const_RelocationRequestAcknowledge(const RelocationRequestAcknowledge &);
    const RelocationRequestAcknowledge *get_const_RelocationRequestAcknowledge() const;
    void set_const_RAB_SetupList_RelocReqAck(const RAB_SetupList_RelocReqAck &);
    const RAB_SetupList_RelocReqAck *get_const_RAB_SetupList_RelocReqAck() const;
    void set_const_RAB_SetupItem_RelocReqAck(const RAB_SetupItem_RelocReqAck &);
    const RAB_SetupItem_RelocReqAck *get_const_RAB_SetupItem_RelocReqAck() const;
    void set_const_RAB_FailedList(const RAB_FailedList &);
    const RAB_FailedList *get_const_RAB_FailedList() const;
    void set_const_RAB_FailedItem(const RAB_FailedItem &);
    const RAB_FailedItem *get_const_RAB_FailedItem() const;
    void set_const_RelocationFailure(const RelocationFailure &);
    const RelocationFailure *get_const_RelocationFailure() const;
    void set_const_RelocationCancel(const RelocationCancel &);
    const RelocationCancel *get_const_RelocationCancel() const;
    void set_const_RelocationCancelAcknowledge(const RelocationCancelAcknowledge &);
    const RelocationCancelAcknowledge *get_const_RelocationCancelAcknowledge() const;
    void set_const_SRNS_ContextRequest(const SRNS_ContextRequest &);
    const SRNS_ContextRequest *get_const_SRNS_ContextRequest() const;
    void set_const_RAB_DataForwardingList_SRNS_CtxReq(const RAB_DataForwardingList_SRNS_CtxReq &);
    const RAB_DataForwardingList_SRNS_CtxReq *get_const_RAB_DataForwardingList_SRNS_CtxReq() const;
    void set_const_RAB_DataForwardingItem_SRNS_CtxReq(const RAB_DataForwardingItem_SRNS_CtxReq &);
    const RAB_DataForwardingItem_SRNS_CtxReq *get_const_RAB_DataForwardingItem_SRNS_CtxReq() const;
    void set_const_SRNS_ContextResponse(const SRNS_ContextResponse &);
    const SRNS_ContextResponse *get_const_SRNS_ContextResponse() const;
    void set_const_RAB_ContextList(const RAB_ContextList &);
    const RAB_ContextList *get_const_RAB_ContextList() const;
    void set_const_RAB_ContextItem(const RAB_ContextItem &);
    const RAB_ContextItem *get_const_RAB_ContextItem() const;
    void set_const_RAB_ContextFailedtoTransferList(const RAB_ContextFailedtoTransferList &);
    const RAB_ContextFailedtoTransferList *get_const_RAB_ContextFailedtoTransferList() const;
    void set_const_RABs_ContextFailedtoTransferItem(const RABs_ContextFailedtoTransferItem &);
    const RABs_ContextFailedtoTransferItem *get_const_RABs_ContextFailedtoTransferItem() const;
    void set_const_SecurityModeCommand(const SecurityModeCommand &);
    const SecurityModeCommand *get_const_SecurityModeCommand() const;
    void set_const_SecurityModeComplete(const SecurityModeComplete &);
    const SecurityModeComplete *get_const_SecurityModeComplete() const;
    void set_const_SecurityModeReject(const SecurityModeReject &);
    const SecurityModeReject *get_const_SecurityModeReject() const;
    void set_const_DataVolumeReportRequest(const DataVolumeReportRequest &);
    const DataVolumeReportRequest *get_const_DataVolumeReportRequest() const;
    void set_const_RAB_DataVolumeReportRequestList(const RAB_DataVolumeReportRequestList &);
    const RAB_DataVolumeReportRequestList *get_const_RAB_DataVolumeReportRequestList() const;
    void set_const_RAB_DataVolumeReportRequestItem(const RAB_DataVolumeReportRequestItem &);
    const RAB_DataVolumeReportRequestItem *get_const_RAB_DataVolumeReportRequestItem() const;
    void set_const_DataVolumeReport(const DataVolumeReport &);
    const DataVolumeReport *get_const_DataVolumeReport() const;
    void set_const_RAB_FailedtoReportList(const RAB_FailedtoReportList &);
    const RAB_FailedtoReportList *get_const_RAB_FailedtoReportList() const;
    void set_const_RABs_failed_to_reportItem(const RABs_failed_to_reportItem &);
    const RABs_failed_to_reportItem *get_const_RABs_failed_to_reportItem() const;
    void set_const_Reset(const Reset &);
    const Reset *get_const_Reset() const;
    void set_const_ResetAcknowledge(const ResetAcknowledge &);
    const ResetAcknowledge *get_const_ResetAcknowledge() const;
    void set_const_ResetResource(const ResetResource &);
    const ResetResource *get_const_ResetResource() const;
    void set_const_ResetResourceList(const ResetResourceList &);
    const ResetResourceList *get_const_ResetResourceList() const;
    void set_const_ResetResourceItem(const ResetResourceItem &);
    const ResetResourceItem *get_const_ResetResourceItem() const;
    void set_const_ResetResourceAcknowledge(const ResetResourceAcknowledge &);
    const ResetResourceAcknowledge *get_const_ResetResourceAcknowledge() const;
    void set_const_ResetResourceAckList(const ResetResourceAckList &);
    const ResetResourceAckList *get_const_ResetResourceAckList() const;
    void set_const_ResetResourceAckItem(const ResetResourceAckItem &);
    const ResetResourceAckItem *get_const_ResetResourceAckItem() const;
    void set_const_RAB_ReleaseRequest(const RAB_ReleaseRequest &);
    const RAB_ReleaseRequest *get_const_RAB_ReleaseRequest() const;
    void set_const_RAB_ReleaseList(const RAB_ReleaseList &);
    const RAB_ReleaseList *get_const_RAB_ReleaseList() const;
    void set_const_RAB_ReleaseItem(const RAB_ReleaseItem &);
    const RAB_ReleaseItem *get_const_RAB_ReleaseItem() const;
    void set_const_Iu_ReleaseRequest(const Iu_ReleaseRequest &);
    const Iu_ReleaseRequest *get_const_Iu_ReleaseRequest() const;
    void set_const_RelocationDetect(const RelocationDetect &);
    const RelocationDetect *get_const_RelocationDetect() const;
    void set_const_RelocationComplete(const RelocationComplete &);
    const RelocationComplete *get_const_RelocationComplete() const;
    void set_const_Paging(const Paging &);
    const Paging *get_const_Paging() const;
    void set_const_CommonID(const CommonID &);
    const CommonID *get_const_CommonID() const;
    void set_const_CN_InvokeTrace(const CN_InvokeTrace &);
    const CN_InvokeTrace *get_const_CN_InvokeTrace() const;
    void set_const_CN_DeactivateTrace(const CN_DeactivateTrace &);
    const CN_DeactivateTrace *get_const_CN_DeactivateTrace() const;
    void set_const_LocationReportingControl(const LocationReportingControl &);
    const LocationReportingControl *get_const_LocationReportingControl() const;
    void set_const_LocationReport(const LocationReport &);
    const LocationReport *get_const_LocationReport() const;
    void set_const_InitialUE_Message(const InitialUE_Message &);
    const InitialUE_Message *get_const_InitialUE_Message() const;
    void set_const_DirectTransfer(const DirectTransfer &);
    const DirectTransfer *get_const_DirectTransfer() const;
    void set_const_Overload(const Overload &);
    const Overload *get_const_Overload() const;
    void set_const_ErrorIndication(const ErrorIndication &);
    const ErrorIndication *get_const_ErrorIndication() const;
    void set_const_SRNS_DataForwardCommand(const SRNS_DataForwardCommand &);
    const SRNS_DataForwardCommand *get_const_SRNS_DataForwardCommand() const;
    void set_const_ForwardSRNS_Context(const ForwardSRNS_Context &);
    const ForwardSRNS_Context *get_const_ForwardSRNS_Context() const;
    void set_const_RAB_AssignmentRequest(const RAB_AssignmentRequest &);
    const RAB_AssignmentRequest *get_const_RAB_AssignmentRequest() const;
    void set_const_RAB_SetupOrModifyList(const RAB_SetupOrModifyList &);
    const RAB_SetupOrModifyList *get_const_RAB_SetupOrModifyList() const;
    void set_const_RAB_SetupOrModifyItemFirst(const RAB_SetupOrModifyItemFirst &);
    const RAB_SetupOrModifyItemFirst *get_const_RAB_SetupOrModifyItemFirst() const;
    void set_const_RAB_SetupOrModifyItemSecond(const RAB_SetupOrModifyItemSecond &);
    const RAB_SetupOrModifyItemSecond *get_const_RAB_SetupOrModifyItemSecond() const;
    void set_const_RAB_AssignmentResponse(const RAB_AssignmentResponse &);
    const RAB_AssignmentResponse *get_const_RAB_AssignmentResponse() const;
    void set_const_RAB_SetupOrModifiedList(const RAB_SetupOrModifiedList &);
    const RAB_SetupOrModifiedList *get_const_RAB_SetupOrModifiedList() const;
    void set_const_RAB_SetupOrModifiedItem(const RAB_SetupOrModifiedItem &);
    const RAB_SetupOrModifiedItem *get_const_RAB_SetupOrModifiedItem() const;
    void set_const_RAB_ReleasedList(const RAB_ReleasedList &);
    const RAB_ReleasedList *get_const_RAB_ReleasedList() const;
    void set_const_RAB_ReleasedItem(const RAB_ReleasedItem &);
    const RAB_ReleasedItem *get_const_RAB_ReleasedItem() const;
    void set_const_RAB_QueuedList(const RAB_QueuedList &);
    const RAB_QueuedList *get_const_RAB_QueuedList() const;
    void set_const_RAB_QueuedItem(const RAB_QueuedItem &);
    const RAB_QueuedItem *get_const_RAB_QueuedItem() const;
    void set_const_RAB_ReleaseFailedList(const RAB_ReleaseFailedList &);
    const RAB_ReleaseFailedList *get_const_RAB_ReleaseFailedList() const;
    void set_const_GERAN_Iumode_RAB_FailedList_RABAssgntResponse(const GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    const GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_const_GERAN_Iumode_RAB_FailedList_RABAssgntResponse() const;
    void set_const_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item(const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_const_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item() const;
    void set_const_PrivateMessage(const PrivateMessage &);
    const PrivateMessage *get_const_PrivateMessage() const;
    void set_const_RANAP_RelocationInformation(const RANAP_RelocationInformation &);
    const RANAP_RelocationInformation *get_const_RANAP_RelocationInformation() const;
    void set_const_DirectTransferInformationList_RANAP_RelocInf(const DirectTransferInformationList_RANAP_RelocInf &);
    const DirectTransferInformationList_RANAP_RelocInf *get_const_DirectTransferInformationList_RANAP_RelocInf() const;
    void set_const_DirectTransferInformationItem_RANAP_RelocInf(const DirectTransferInformationItem_RANAP_RelocInf &);
    const DirectTransferInformationItem_RANAP_RelocInf *get_const_DirectTransferInformationItem_RANAP_RelocInf() const;
    void set_const_RAB_ContextList_RANAP_RelocInf(const RAB_ContextList_RANAP_RelocInf &);
    const RAB_ContextList_RANAP_RelocInf *get_const_RAB_ContextList_RANAP_RelocInf() const;
    void set_const_RAB_ContextItem_RANAP_RelocInf(const RAB_ContextItem_RANAP_RelocInf &);
    const RAB_ContextItem_RANAP_RelocInf *get_const_RAB_ContextItem_RANAP_RelocInf() const;
    void set_const_RAB_ModifyRequest(const RAB_ModifyRequest &);
    const RAB_ModifyRequest *get_const_RAB_ModifyRequest() const;
    void set_const_RAB_ModifyList(const RAB_ModifyList &);
    const RAB_ModifyList *get_const_RAB_ModifyList() const;
    void set_const_RAB_ModifyItem(const RAB_ModifyItem &);
    const RAB_ModifyItem *get_const_RAB_ModifyItem() const;
    void set_const_LocationRelatedDataRequest(const LocationRelatedDataRequest &);
    const LocationRelatedDataRequest *get_const_LocationRelatedDataRequest() const;
    void set_const_LocationRelatedDataResponse(const LocationRelatedDataResponse &);
    const LocationRelatedDataResponse *get_const_LocationRelatedDataResponse() const;
    void set_const_LocationRelatedDataFailure(const LocationRelatedDataFailure &);
    const LocationRelatedDataFailure *get_const_LocationRelatedDataFailure() const;
    void set_const_InformationTransferIndication(const InformationTransferIndication &);
    const InformationTransferIndication *get_const_InformationTransferIndication() const;
    void set_const_InformationTransferConfirmation(const InformationTransferConfirmation &);
    const InformationTransferConfirmation *get_const_InformationTransferConfirmation() const;
    void set_const_InformationTransferFailure(const InformationTransferFailure &);
    const InformationTransferFailure *get_const_InformationTransferFailure() const;
    void set_const_UESpecificInformationIndication(const UESpecificInformationIndication &);
    const UESpecificInformationIndication *get_const_UESpecificInformationIndication() const;
    void set_const_DirectInformationTransfer(const DirectInformationTransfer &);
    const DirectInformationTransfer *get_const_DirectInformationTransfer() const;
    void set_const_UplinkInformationTransferIndication(const UplinkInformationTransferIndication &);
    const UplinkInformationTransferIndication *get_const_UplinkInformationTransferIndication() const;
    void set_const_UplinkInformationTransferConfirmation(const UplinkInformationTransferConfirmation &);
    const UplinkInformationTransferConfirmation *get_const_UplinkInformationTransferConfirmation() const;
    void set_const_UplinkInformationTransferFailure(const UplinkInformationTransferFailure &);
    const UplinkInformationTransferFailure *get_const_UplinkInformationTransferFailure() const;
#endif
};

/* Specific PDU classes */

class OSS_PUBLIC RANAP_PDU_PDU : public ConcretePDU {
public:
    RANAP_PDU_PDU();
    void set_data(RANAP_PDU &);
    RANAP_PDU *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RANAP_PDU & d);
    const RANAP_PDU *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC AccuracyFulfilmentIndicator_PDU : public ConcretePDU {
public:
    AccuracyFulfilmentIndicator_PDU();
    void set_data(AccuracyFulfilmentIndicator &);
    AccuracyFulfilmentIndicator *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const AccuracyFulfilmentIndicator & d);
    const AccuracyFulfilmentIndicator *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Alt_RAB_Parameters_PDU : public ConcretePDU {
public:
    Alt_RAB_Parameters_PDU();
    void set_data(Alt_RAB_Parameters &);
    Alt_RAB_Parameters *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Alt_RAB_Parameters & d);
    const Alt_RAB_Parameters *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC AreaIdentity_PDU : public ConcretePDU {
public:
    AreaIdentity_PDU();
    void set_data(AreaIdentity &);
    AreaIdentity *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const AreaIdentity & d);
    const AreaIdentity *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Ass_RAB_Parameters_PDU : public ConcretePDU {
public:
    Ass_RAB_Parameters_PDU();
    void set_data(Ass_RAB_Parameters &);
    Ass_RAB_Parameters *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Ass_RAB_Parameters & d);
    const Ass_RAB_Parameters *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC BroadcastAssistanceDataDecipheringKeys_PDU : public ConcretePDU {
public:
    BroadcastAssistanceDataDecipheringKeys_PDU();
    void set_data(BroadcastAssistanceDataDecipheringKeys &);
    BroadcastAssistanceDataDecipheringKeys *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const BroadcastAssistanceDataDecipheringKeys & d);
    const BroadcastAssistanceDataDecipheringKeys *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Cause_PDU : public ConcretePDU {
public:
    Cause_PDU();
    void set_data(Cause &);
    Cause *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Cause & d);
    const Cause *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CellLoadInformationGroup_PDU : public ConcretePDU {
public:
    CellLoadInformationGroup_PDU();
    void set_data(CellLoadInformationGroup &);
    CellLoadInformationGroup *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CellLoadInformationGroup & d);
    const CellLoadInformationGroup *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ClientType_PDU : public ConcretePDU {
public:
    ClientType_PDU();
    void set_data(ClientType &);
    ClientType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ClientType & d);
    const ClientType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CriticalityDiagnostics_PDU : public ConcretePDU {
public:
    CriticalityDiagnostics_PDU();
    void set_data(CriticalityDiagnostics &);
    CriticalityDiagnostics *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CriticalityDiagnostics & d);
    const CriticalityDiagnostics *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC MessageStructure_PDU : public ConcretePDU {
public:
    MessageStructure_PDU();
    void set_data(MessageStructure &);
    MessageStructure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const MessageStructure & d);
    const MessageStructure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ChosenEncryptionAlgorithm_PDU : public ConcretePDU {
public:
    ChosenEncryptionAlgorithm_PDU();
    void set_data(ChosenEncryptionAlgorithm &);
    ChosenEncryptionAlgorithm *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ChosenEncryptionAlgorithm & d);
    const ChosenEncryptionAlgorithm *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ChosenIntegrityProtectionAlgorithm_PDU : public ConcretePDU {
public:
    ChosenIntegrityProtectionAlgorithm_PDU();
    void set_data(ChosenIntegrityProtectionAlgorithm &);
    ChosenIntegrityProtectionAlgorithm *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ChosenIntegrityProtectionAlgorithm & d);
    const ChosenIntegrityProtectionAlgorithm *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ClassmarkInformation2_PDU : public ConcretePDU {
public:
    ClassmarkInformation2_PDU();
    void set_data(ClassmarkInformation2 &);
    ClassmarkInformation2 *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ClassmarkInformation2 & d);
    const ClassmarkInformation2 *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ClassmarkInformation3_PDU : public ConcretePDU {
public:
    ClassmarkInformation3_PDU();
    void set_data(ClassmarkInformation3 &);
    ClassmarkInformation3 *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ClassmarkInformation3 & d);
    const ClassmarkInformation3 *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CN_DomainIndicator_PDU : public ConcretePDU {
public:
    CN_DomainIndicator_PDU();
    void set_data(CN_DomainIndicator &);
    CN_DomainIndicator *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CN_DomainIndicator & d);
    const CN_DomainIndicator *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DRX_CycleLengthCoefficient_PDU : public ConcretePDU {
public:
    DRX_CycleLengthCoefficient_PDU();
    void set_data(DRX_CycleLengthCoefficient &);
    DRX_CycleLengthCoefficient *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DRX_CycleLengthCoefficient & d);
    const DRX_CycleLengthCoefficient *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC EncryptionInformation_PDU : public ConcretePDU {
public:
    EncryptionInformation_PDU();
    void set_data(EncryptionInformation &);
    EncryptionInformation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const EncryptionInformation & d);
    const EncryptionInformation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GERAN_BSC_Container_PDU : public ConcretePDU {
public:
    GERAN_BSC_Container_PDU();
    void set_data(GERAN_BSC_Container &);
    GERAN_BSC_Container *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GERAN_BSC_Container & d);
    const GERAN_BSC_Container *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GERAN_Classmark_PDU : public ConcretePDU {
public:
    GERAN_Classmark_PDU();
    void set_data(GERAN_Classmark &);
    GERAN_Classmark *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GERAN_Classmark & d);
    const GERAN_Classmark *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GlobalCN_ID_PDU : public ConcretePDU {
public:
    GlobalCN_ID_PDU();
    void set_data(GlobalCN_ID &);
    GlobalCN_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GlobalCN_ID & d);
    const GlobalCN_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GlobalRNC_ID_PDU : public ConcretePDU {
public:
    GlobalRNC_ID_PDU();
    void set_data(GlobalRNC_ID &);
    GlobalRNC_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GlobalRNC_ID & d);
    const GlobalRNC_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC HS_DSCH_MAC_d_Flow_ID_PDU : public ConcretePDU {
public:
    HS_DSCH_MAC_d_Flow_ID_PDU();
    void set_data(HS_DSCH_MAC_d_Flow_ID &);
    HS_DSCH_MAC_d_Flow_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const HS_DSCH_MAC_d_Flow_ID & d);
    const HS_DSCH_MAC_d_Flow_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InformationTransferID_PDU : public ConcretePDU {
public:
    InformationTransferID_PDU();
    void set_data(InformationTransferID &);
    InformationTransferID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InformationTransferID & d);
    const InformationTransferID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InformationTransferType_PDU : public ConcretePDU {
public:
    InformationTransferType_PDU();
    void set_data(InformationTransferType &);
    InformationTransferType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InformationTransferType & d);
    const InformationTransferType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC IntegrityProtectionInformation_PDU : public ConcretePDU {
public:
    IntegrityProtectionInformation_PDU();
    void set_data(IntegrityProtectionInformation &);
    IntegrityProtectionInformation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const IntegrityProtectionInformation & d);
    const IntegrityProtectionInformation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InterSystemInformationTransferType_PDU : public ConcretePDU {
public:
    InterSystemInformationTransferType_PDU();
    void set_data(InterSystemInformationTransferType &);
    InterSystemInformationTransferType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InterSystemInformationTransferType & d);
    const InterSystemInformationTransferType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InterSystemInformation_TransparentContainer_PDU : public ConcretePDU {
public:
    InterSystemInformation_TransparentContainer_PDU();
    void set_data(InterSystemInformation_TransparentContainer &);
    InterSystemInformation_TransparentContainer *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InterSystemInformation_TransparentContainer & d);
    const InterSystemInformation_TransparentContainer *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC IuSignallingConnectionIdentifier_PDU : public ConcretePDU {
public:
    IuSignallingConnectionIdentifier_PDU();
    void set_data(IuSignallingConnectionIdentifier &);
    IuSignallingConnectionIdentifier *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const IuSignallingConnectionIdentifier & d);
    const IuSignallingConnectionIdentifier *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC IuTransportAssociation_PDU : public ConcretePDU {
public:
    IuTransportAssociation_PDU();
    void set_data(IuTransportAssociation &);
    IuTransportAssociation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const IuTransportAssociation & d);
    const IuTransportAssociation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC KeyStatus_PDU : public ConcretePDU {
public:
    KeyStatus_PDU();
    void set_data(KeyStatus &);
    KeyStatus *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const KeyStatus & d);
    const KeyStatus *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LAI_PDU : public ConcretePDU {
public:
    LAI_PDU();
    void set_data(LAI &);
    LAI *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LAI & d);
    const LAI *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LastKnownServiceArea_PDU : public ConcretePDU {
public:
    LastKnownServiceArea_PDU();
    void set_data(LastKnownServiceArea &);
    LastKnownServiceArea *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LastKnownServiceArea & d);
    const LastKnownServiceArea *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationRelatedDataRequestType_PDU : public ConcretePDU {
public:
    LocationRelatedDataRequestType_PDU();
    void set_data(LocationRelatedDataRequestType &);
    LocationRelatedDataRequestType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationRelatedDataRequestType & d);
    const LocationRelatedDataRequestType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationRelatedDataRequestTypeSpecificToGERANIuMode_PDU : public ConcretePDU {
public:
    LocationRelatedDataRequestTypeSpecificToGERANIuMode_PDU();
    void set_data(LocationRelatedDataRequestTypeSpecificToGERANIuMode &);
    LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationRelatedDataRequestTypeSpecificToGERANIuMode & d);
    const LocationRelatedDataRequestTypeSpecificToGERANIuMode *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC L3_Information_PDU : public ConcretePDU {
public:
    L3_Information_PDU();
    void set_data(L3_Information &);
    L3_Information *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const L3_Information & d);
    const L3_Information *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC NAS_PDU_PDU : public ConcretePDU {
public:
    NAS_PDU_PDU();
    void set_data(NAS_PDU &);
    NAS_PDU *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const NAS_PDU & d);
    const NAS_PDU *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC NewBSS_To_OldBSS_Information_PDU : public ConcretePDU {
public:
    NewBSS_To_OldBSS_Information_PDU();
    void set_data(NewBSS_To_OldBSS_Information &);
    NewBSS_To_OldBSS_Information *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const NewBSS_To_OldBSS_Information & d);
    const NewBSS_To_OldBSS_Information *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC NonSearchingIndication_PDU : public ConcretePDU {
public:
    NonSearchingIndication_PDU();
    void set_data(NonSearchingIndication &);
    NonSearchingIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const NonSearchingIndication & d);
    const NonSearchingIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC NumberOfSteps_PDU : public ConcretePDU {
public:
    NumberOfSteps_PDU();
    void set_data(NumberOfSteps &);
    NumberOfSteps *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const NumberOfSteps & d);
    const NumberOfSteps *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC OldBSS_ToNewBSS_Information_PDU : public ConcretePDU {
public:
    OldBSS_ToNewBSS_Information_PDU();
    void set_data(OldBSS_ToNewBSS_Information &);
    OldBSS_ToNewBSS_Information *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const OldBSS_ToNewBSS_Information & d);
    const OldBSS_ToNewBSS_Information *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC OMC_ID_PDU : public ConcretePDU {
public:
    OMC_ID_PDU();
    void set_data(OMC_ID &);
    OMC_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const OMC_ID & d);
    const OMC_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PagingAreaID_PDU : public ConcretePDU {
public:
    PagingAreaID_PDU();
    void set_data(PagingAreaID &);
    PagingAreaID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PagingAreaID & d);
    const PagingAreaID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PagingCause_PDU : public ConcretePDU {
public:
    PagingCause_PDU();
    void set_data(PagingCause &);
    PagingCause *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PagingCause & d);
    const PagingCause *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PermanentNAS_UE_ID_PDU : public ConcretePDU {
public:
    PermanentNAS_UE_ID_PDU();
    void set_data(PermanentNAS_UE_ID &);
    PermanentNAS_UE_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PermanentNAS_UE_ID & d);
    const PermanentNAS_UE_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PositioningPriority_PDU : public ConcretePDU {
public:
    PositioningPriority_PDU();
    void set_data(PositioningPriority &);
    PositioningPriority *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PositioningPriority & d);
    const PositioningPriority *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PositionData_PDU : public ConcretePDU {
public:
    PositionData_PDU();
    void set_data(PositionData &);
    PositionData *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PositionData & d);
    const PositionData *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PositionDataSpecificToGERANIuMode_PDU : public ConcretePDU {
public:
    PositionDataSpecificToGERANIuMode_PDU();
    void set_data(PositionDataSpecificToGERANIuMode &);
    PositionDataSpecificToGERANIuMode *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PositionDataSpecificToGERANIuMode & d);
    const PositionDataSpecificToGERANIuMode *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ProvidedData_PDU : public ConcretePDU {
public:
    ProvidedData_PDU();
    void set_data(ProvidedData &);
    ProvidedData *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ProvidedData & d);
    const ProvidedData *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAC_PDU : public ConcretePDU {
public:
    RAC_PDU();
    void set_data(RAC &);
    RAC *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAC & d);
    const RAC *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RateControlAllowed_PDU : public ConcretePDU {
public:
    RateControlAllowed_PDU();
    void set_data(RateControlAllowed &);
    RateControlAllowed *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RateControlAllowed & d);
    const RateControlAllowed *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationType_PDU : public ConcretePDU {
public:
    RelocationType_PDU();
    void set_data(RelocationType &);
    RelocationType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationType & d);
    const RelocationType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RequestType_PDU : public ConcretePDU {
public:
    RequestType_PDU();
    void set_data(RequestType &);
    RequestType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RequestType & d);
    const RequestType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResponseTime_PDU : public ConcretePDU {
public:
    ResponseTime_PDU();
    void set_data(ResponseTime &);
    ResponseTime *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResponseTime & d);
    const ResponseTime *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RRC_Container_PDU : public ConcretePDU {
public:
    RRC_Container_PDU();
    void set_data(RRC_Container &);
    RRC_Container *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RRC_Container & d);
    const RRC_Container *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SAI_PDU : public ConcretePDU {
public:
    SAI_PDU();
    void set_data(SAI &);
    SAI *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SAI & d);
    const SAI *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SAPI_PDU : public ConcretePDU {
public:
    SAPI_PDU();
    void set_data(SAPI &);
    SAPI *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SAPI & d);
    const SAPI *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SignallingIndication_PDU : public ConcretePDU {
public:
    SignallingIndication_PDU();
    void set_data(SignallingIndication &);
    SignallingIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SignallingIndication & d);
    const SignallingIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SNA_Access_Information_PDU : public ConcretePDU {
public:
    SNA_Access_Information_PDU();
    void set_data(SNA_Access_Information &);
    SNA_Access_Information *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SNA_Access_Information & d);
    const SNA_Access_Information *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SourceID_PDU : public ConcretePDU {
public:
    SourceID_PDU();
    void set_data(SourceID &);
    SourceID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SourceID & d);
    const SourceID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SourceRNC_ToTargetRNC_TransparentContainer_PDU : public ConcretePDU {
public:
    SourceRNC_ToTargetRNC_TransparentContainer_PDU();
    void set_data(SourceRNC_ToTargetRNC_TransparentContainer &);
    SourceRNC_ToTargetRNC_TransparentContainer *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SourceRNC_ToTargetRNC_TransparentContainer & d);
    const SourceRNC_ToTargetRNC_TransparentContainer *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SRB_TrCH_Mapping_PDU : public ConcretePDU {
public:
    SRB_TrCH_Mapping_PDU();
    void set_data(SRB_TrCH_Mapping &);
    SRB_TrCH_Mapping *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SRB_TrCH_Mapping & d);
    const SRB_TrCH_Mapping *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TargetID_PDU : public ConcretePDU {
public:
    TargetID_PDU();
    void set_data(TargetID &);
    TargetID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TargetID & d);
    const TargetID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TargetRNC_ToSourceRNC_TransparentContainer_PDU : public ConcretePDU {
public:
    TargetRNC_ToSourceRNC_TransparentContainer_PDU();
    void set_data(TargetRNC_ToSourceRNC_TransparentContainer &);
    TargetRNC_ToSourceRNC_TransparentContainer *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TargetRNC_ToSourceRNC_TransparentContainer & d);
    const TargetRNC_ToSourceRNC_TransparentContainer *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TemporaryUE_ID_PDU : public ConcretePDU {
public:
    TemporaryUE_ID_PDU();
    void set_data(TemporaryUE_ID &);
    TemporaryUE_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TemporaryUE_ID & d);
    const TemporaryUE_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TracePropagationParameters_PDU : public ConcretePDU {
public:
    TracePropagationParameters_PDU();
    void set_data(TracePropagationParameters &);
    TracePropagationParameters *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TracePropagationParameters & d);
    const TracePropagationParameters *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TraceRecordingSessionInformation_PDU : public ConcretePDU {
public:
    TraceRecordingSessionInformation_PDU();
    void set_data(TraceRecordingSessionInformation &);
    TraceRecordingSessionInformation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TraceRecordingSessionInformation & d);
    const TraceRecordingSessionInformation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TraceReference_PDU : public ConcretePDU {
public:
    TraceReference_PDU();
    void set_data(TraceReference &);
    TraceReference *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TraceReference & d);
    const TraceReference *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TraceType_PDU : public ConcretePDU {
public:
    TraceType_PDU();
    void set_data(TraceType &);
    TraceType *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TraceType & d);
    const TraceType *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TransportLayerAddress_PDU : public ConcretePDU {
public:
    TransportLayerAddress_PDU();
    void set_data(TransportLayerAddress &);
    TransportLayerAddress *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TransportLayerAddress & d);
    const TransportLayerAddress *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TriggerID_PDU : public ConcretePDU {
public:
    TriggerID_PDU();
    void set_data(TriggerID &);
    TriggerID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TriggerID & d);
    const TriggerID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC TypeOfError_PDU : public ConcretePDU {
public:
    TypeOfError_PDU();
    void set_data(TypeOfError &);
    TypeOfError *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const TypeOfError & d);
    const TypeOfError *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UE_ID_PDU : public ConcretePDU {
public:
    UE_ID_PDU();
    void set_data(UE_ID &);
    UE_ID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UE_ID & d);
    const UE_ID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UESBI_Iu_PDU : public ConcretePDU {
public:
    UESBI_Iu_PDU();
    void set_data(UESBI_Iu &);
    UESBI_Iu *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UESBI_Iu & d);
    const UESBI_Iu *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC VerticalAccuracyCode_PDU : public ConcretePDU {
public:
    VerticalAccuracyCode_PDU();
    void set_data(VerticalAccuracyCode &);
    VerticalAccuracyCode *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const VerticalAccuracyCode & d);
    const VerticalAccuracyCode *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Iu_ReleaseCommand_PDU : public ConcretePDU {
public:
    Iu_ReleaseCommand_PDU();
    void set_data(Iu_ReleaseCommand &);
    Iu_ReleaseCommand *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Iu_ReleaseCommand & d);
    const Iu_ReleaseCommand *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Iu_ReleaseComplete_PDU : public ConcretePDU {
public:
    Iu_ReleaseComplete_PDU();
    void set_data(Iu_ReleaseComplete &);
    Iu_ReleaseComplete *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Iu_ReleaseComplete & d);
    const Iu_ReleaseComplete *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataVolumeReportList_PDU : public ConcretePDU {
public:
    RAB_DataVolumeReportList_PDU();
    void set_data(RAB_DataVolumeReportList &);
    RAB_DataVolumeReportList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataVolumeReportList & d);
    const RAB_DataVolumeReportList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataVolumeReportItem_PDU : public ConcretePDU {
public:
    RAB_DataVolumeReportItem_PDU();
    void set_data(RAB_DataVolumeReportItem &);
    RAB_DataVolumeReportItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataVolumeReportItem & d);
    const RAB_DataVolumeReportItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleasedList_IuRelComp_PDU : public ConcretePDU {
public:
    RAB_ReleasedList_IuRelComp_PDU();
    void set_data(RAB_ReleasedList_IuRelComp &);
    RAB_ReleasedList_IuRelComp *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleasedList_IuRelComp & d);
    const RAB_ReleasedList_IuRelComp *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleasedItem_IuRelComp_PDU : public ConcretePDU {
public:
    RAB_ReleasedItem_IuRelComp_PDU();
    void set_data(RAB_ReleasedItem_IuRelComp &);
    RAB_ReleasedItem_IuRelComp *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleasedItem_IuRelComp & d);
    const RAB_ReleasedItem_IuRelComp *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationRequired_PDU : public ConcretePDU {
public:
    RelocationRequired_PDU();
    void set_data(RelocationRequired &);
    RelocationRequired *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationRequired & d);
    const RelocationRequired *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationCommand_PDU : public ConcretePDU {
public:
    RelocationCommand_PDU();
    void set_data(RelocationCommand &);
    RelocationCommand *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationCommand & d);
    const RelocationCommand *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_RelocationReleaseList_PDU : public ConcretePDU {
public:
    RAB_RelocationReleaseList_PDU();
    void set_data(RAB_RelocationReleaseList &);
    RAB_RelocationReleaseList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_RelocationReleaseList & d);
    const RAB_RelocationReleaseList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_RelocationReleaseItem_PDU : public ConcretePDU {
public:
    RAB_RelocationReleaseItem_PDU();
    void set_data(RAB_RelocationReleaseItem &);
    RAB_RelocationReleaseItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_RelocationReleaseItem & d);
    const RAB_RelocationReleaseItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataForwardingList_PDU : public ConcretePDU {
public:
    RAB_DataForwardingList_PDU();
    void set_data(RAB_DataForwardingList &);
    RAB_DataForwardingList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataForwardingList & d);
    const RAB_DataForwardingList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataForwardingItem_PDU : public ConcretePDU {
public:
    RAB_DataForwardingItem_PDU();
    void set_data(RAB_DataForwardingItem &);
    RAB_DataForwardingItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataForwardingItem & d);
    const RAB_DataForwardingItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationPreparationFailure_PDU : public ConcretePDU {
public:
    RelocationPreparationFailure_PDU();
    void set_data(RelocationPreparationFailure &);
    RelocationPreparationFailure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationPreparationFailure & d);
    const RelocationPreparationFailure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationRequest_PDU : public ConcretePDU {
public:
    RelocationRequest_PDU();
    void set_data(RelocationRequest &);
    RelocationRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationRequest & d);
    const RelocationRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupList_RelocReq_PDU : public ConcretePDU {
public:
    RAB_SetupList_RelocReq_PDU();
    void set_data(RAB_SetupList_RelocReq &);
    RAB_SetupList_RelocReq *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupList_RelocReq & d);
    const RAB_SetupList_RelocReq *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupItem_RelocReq_PDU : public ConcretePDU {
public:
    RAB_SetupItem_RelocReq_PDU();
    void set_data(RAB_SetupItem_RelocReq &);
    RAB_SetupItem_RelocReq *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupItem_RelocReq & d);
    const RAB_SetupItem_RelocReq *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationRequestAcknowledge_PDU : public ConcretePDU {
public:
    RelocationRequestAcknowledge_PDU();
    void set_data(RelocationRequestAcknowledge &);
    RelocationRequestAcknowledge *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationRequestAcknowledge & d);
    const RelocationRequestAcknowledge *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupList_RelocReqAck_PDU : public ConcretePDU {
public:
    RAB_SetupList_RelocReqAck_PDU();
    void set_data(RAB_SetupList_RelocReqAck &);
    RAB_SetupList_RelocReqAck *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupList_RelocReqAck & d);
    const RAB_SetupList_RelocReqAck *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupItem_RelocReqAck_PDU : public ConcretePDU {
public:
    RAB_SetupItem_RelocReqAck_PDU();
    void set_data(RAB_SetupItem_RelocReqAck &);
    RAB_SetupItem_RelocReqAck *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupItem_RelocReqAck & d);
    const RAB_SetupItem_RelocReqAck *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_FailedList_PDU : public ConcretePDU {
public:
    RAB_FailedList_PDU();
    void set_data(RAB_FailedList &);
    RAB_FailedList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_FailedList & d);
    const RAB_FailedList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_FailedItem_PDU : public ConcretePDU {
public:
    RAB_FailedItem_PDU();
    void set_data(RAB_FailedItem &);
    RAB_FailedItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_FailedItem & d);
    const RAB_FailedItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationFailure_PDU : public ConcretePDU {
public:
    RelocationFailure_PDU();
    void set_data(RelocationFailure &);
    RelocationFailure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationFailure & d);
    const RelocationFailure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationCancel_PDU : public ConcretePDU {
public:
    RelocationCancel_PDU();
    void set_data(RelocationCancel &);
    RelocationCancel *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationCancel & d);
    const RelocationCancel *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationCancelAcknowledge_PDU : public ConcretePDU {
public:
    RelocationCancelAcknowledge_PDU();
    void set_data(RelocationCancelAcknowledge &);
    RelocationCancelAcknowledge *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationCancelAcknowledge & d);
    const RelocationCancelAcknowledge *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SRNS_ContextRequest_PDU : public ConcretePDU {
public:
    SRNS_ContextRequest_PDU();
    void set_data(SRNS_ContextRequest &);
    SRNS_ContextRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SRNS_ContextRequest & d);
    const SRNS_ContextRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataForwardingList_SRNS_CtxReq_PDU : public ConcretePDU {
public:
    RAB_DataForwardingList_SRNS_CtxReq_PDU();
    void set_data(RAB_DataForwardingList_SRNS_CtxReq &);
    RAB_DataForwardingList_SRNS_CtxReq *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataForwardingList_SRNS_CtxReq & d);
    const RAB_DataForwardingList_SRNS_CtxReq *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataForwardingItem_SRNS_CtxReq_PDU : public ConcretePDU {
public:
    RAB_DataForwardingItem_SRNS_CtxReq_PDU();
    void set_data(RAB_DataForwardingItem_SRNS_CtxReq &);
    RAB_DataForwardingItem_SRNS_CtxReq *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataForwardingItem_SRNS_CtxReq & d);
    const RAB_DataForwardingItem_SRNS_CtxReq *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SRNS_ContextResponse_PDU : public ConcretePDU {
public:
    SRNS_ContextResponse_PDU();
    void set_data(SRNS_ContextResponse &);
    SRNS_ContextResponse *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SRNS_ContextResponse & d);
    const SRNS_ContextResponse *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ContextList_PDU : public ConcretePDU {
public:
    RAB_ContextList_PDU();
    void set_data(RAB_ContextList &);
    RAB_ContextList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ContextList & d);
    const RAB_ContextList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ContextItem_PDU : public ConcretePDU {
public:
    RAB_ContextItem_PDU();
    void set_data(RAB_ContextItem &);
    RAB_ContextItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ContextItem & d);
    const RAB_ContextItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ContextFailedtoTransferList_PDU : public ConcretePDU {
public:
    RAB_ContextFailedtoTransferList_PDU();
    void set_data(RAB_ContextFailedtoTransferList &);
    RAB_ContextFailedtoTransferList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ContextFailedtoTransferList & d);
    const RAB_ContextFailedtoTransferList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RABs_ContextFailedtoTransferItem_PDU : public ConcretePDU {
public:
    RABs_ContextFailedtoTransferItem_PDU();
    void set_data(RABs_ContextFailedtoTransferItem &);
    RABs_ContextFailedtoTransferItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RABs_ContextFailedtoTransferItem & d);
    const RABs_ContextFailedtoTransferItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SecurityModeCommand_PDU : public ConcretePDU {
public:
    SecurityModeCommand_PDU();
    void set_data(SecurityModeCommand &);
    SecurityModeCommand *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SecurityModeCommand & d);
    const SecurityModeCommand *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SecurityModeComplete_PDU : public ConcretePDU {
public:
    SecurityModeComplete_PDU();
    void set_data(SecurityModeComplete &);
    SecurityModeComplete *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SecurityModeComplete & d);
    const SecurityModeComplete *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SecurityModeReject_PDU : public ConcretePDU {
public:
    SecurityModeReject_PDU();
    void set_data(SecurityModeReject &);
    SecurityModeReject *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SecurityModeReject & d);
    const SecurityModeReject *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DataVolumeReportRequest_PDU : public ConcretePDU {
public:
    DataVolumeReportRequest_PDU();
    void set_data(DataVolumeReportRequest &);
    DataVolumeReportRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DataVolumeReportRequest & d);
    const DataVolumeReportRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataVolumeReportRequestList_PDU : public ConcretePDU {
public:
    RAB_DataVolumeReportRequestList_PDU();
    void set_data(RAB_DataVolumeReportRequestList &);
    RAB_DataVolumeReportRequestList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataVolumeReportRequestList & d);
    const RAB_DataVolumeReportRequestList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_DataVolumeReportRequestItem_PDU : public ConcretePDU {
public:
    RAB_DataVolumeReportRequestItem_PDU();
    void set_data(RAB_DataVolumeReportRequestItem &);
    RAB_DataVolumeReportRequestItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_DataVolumeReportRequestItem & d);
    const RAB_DataVolumeReportRequestItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DataVolumeReport_PDU : public ConcretePDU {
public:
    DataVolumeReport_PDU();
    void set_data(DataVolumeReport &);
    DataVolumeReport *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DataVolumeReport & d);
    const DataVolumeReport *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_FailedtoReportList_PDU : public ConcretePDU {
public:
    RAB_FailedtoReportList_PDU();
    void set_data(RAB_FailedtoReportList &);
    RAB_FailedtoReportList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_FailedtoReportList & d);
    const RAB_FailedtoReportList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RABs_failed_to_reportItem_PDU : public ConcretePDU {
public:
    RABs_failed_to_reportItem_PDU();
    void set_data(RABs_failed_to_reportItem &);
    RABs_failed_to_reportItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RABs_failed_to_reportItem & d);
    const RABs_failed_to_reportItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Reset_PDU : public ConcretePDU {
public:
    Reset_PDU();
    void set_data(Reset &);
    Reset *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Reset & d);
    const Reset *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetAcknowledge_PDU : public ConcretePDU {
public:
    ResetAcknowledge_PDU();
    void set_data(ResetAcknowledge &);
    ResetAcknowledge *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetAcknowledge & d);
    const ResetAcknowledge *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResource_PDU : public ConcretePDU {
public:
    ResetResource_PDU();
    void set_data(ResetResource &);
    ResetResource *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResource & d);
    const ResetResource *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResourceList_PDU : public ConcretePDU {
public:
    ResetResourceList_PDU();
    void set_data(ResetResourceList &);
    ResetResourceList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResourceList & d);
    const ResetResourceList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResourceItem_PDU : public ConcretePDU {
public:
    ResetResourceItem_PDU();
    void set_data(ResetResourceItem &);
    ResetResourceItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResourceItem & d);
    const ResetResourceItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResourceAcknowledge_PDU : public ConcretePDU {
public:
    ResetResourceAcknowledge_PDU();
    void set_data(ResetResourceAcknowledge &);
    ResetResourceAcknowledge *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResourceAcknowledge & d);
    const ResetResourceAcknowledge *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResourceAckList_PDU : public ConcretePDU {
public:
    ResetResourceAckList_PDU();
    void set_data(ResetResourceAckList &);
    ResetResourceAckList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResourceAckList & d);
    const ResetResourceAckList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ResetResourceAckItem_PDU : public ConcretePDU {
public:
    ResetResourceAckItem_PDU();
    void set_data(ResetResourceAckItem &);
    ResetResourceAckItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ResetResourceAckItem & d);
    const ResetResourceAckItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleaseRequest_PDU : public ConcretePDU {
public:
    RAB_ReleaseRequest_PDU();
    void set_data(RAB_ReleaseRequest &);
    RAB_ReleaseRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleaseRequest & d);
    const RAB_ReleaseRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleaseList_PDU : public ConcretePDU {
public:
    RAB_ReleaseList_PDU();
    void set_data(RAB_ReleaseList &);
    RAB_ReleaseList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleaseList & d);
    const RAB_ReleaseList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleaseItem_PDU : public ConcretePDU {
public:
    RAB_ReleaseItem_PDU();
    void set_data(RAB_ReleaseItem &);
    RAB_ReleaseItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleaseItem & d);
    const RAB_ReleaseItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Iu_ReleaseRequest_PDU : public ConcretePDU {
public:
    Iu_ReleaseRequest_PDU();
    void set_data(Iu_ReleaseRequest &);
    Iu_ReleaseRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Iu_ReleaseRequest & d);
    const Iu_ReleaseRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationDetect_PDU : public ConcretePDU {
public:
    RelocationDetect_PDU();
    void set_data(RelocationDetect &);
    RelocationDetect *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationDetect & d);
    const RelocationDetect *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RelocationComplete_PDU : public ConcretePDU {
public:
    RelocationComplete_PDU();
    void set_data(RelocationComplete &);
    RelocationComplete *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RelocationComplete & d);
    const RelocationComplete *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Paging_PDU : public ConcretePDU {
public:
    Paging_PDU();
    void set_data(Paging &);
    Paging *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Paging & d);
    const Paging *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CommonID_PDU : public ConcretePDU {
public:
    CommonID_PDU();
    void set_data(CommonID &);
    CommonID *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CommonID & d);
    const CommonID *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CN_InvokeTrace_PDU : public ConcretePDU {
public:
    CN_InvokeTrace_PDU();
    void set_data(CN_InvokeTrace &);
    CN_InvokeTrace *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CN_InvokeTrace & d);
    const CN_InvokeTrace *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC CN_DeactivateTrace_PDU : public ConcretePDU {
public:
    CN_DeactivateTrace_PDU();
    void set_data(CN_DeactivateTrace &);
    CN_DeactivateTrace *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const CN_DeactivateTrace & d);
    const CN_DeactivateTrace *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationReportingControl_PDU : public ConcretePDU {
public:
    LocationReportingControl_PDU();
    void set_data(LocationReportingControl &);
    LocationReportingControl *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationReportingControl & d);
    const LocationReportingControl *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationReport_PDU : public ConcretePDU {
public:
    LocationReport_PDU();
    void set_data(LocationReport &);
    LocationReport *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationReport & d);
    const LocationReport *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InitialUE_Message_PDU : public ConcretePDU {
public:
    InitialUE_Message_PDU();
    void set_data(InitialUE_Message &);
    InitialUE_Message *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InitialUE_Message & d);
    const InitialUE_Message *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DirectTransfer_PDU : public ConcretePDU {
public:
    DirectTransfer_PDU();
    void set_data(DirectTransfer &);
    DirectTransfer *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DirectTransfer & d);
    const DirectTransfer *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC Overload_PDU : public ConcretePDU {
public:
    Overload_PDU();
    void set_data(Overload &);
    Overload *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const Overload & d);
    const Overload *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ErrorIndication_PDU : public ConcretePDU {
public:
    ErrorIndication_PDU();
    void set_data(ErrorIndication &);
    ErrorIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ErrorIndication & d);
    const ErrorIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC SRNS_DataForwardCommand_PDU : public ConcretePDU {
public:
    SRNS_DataForwardCommand_PDU();
    void set_data(SRNS_DataForwardCommand &);
    SRNS_DataForwardCommand *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const SRNS_DataForwardCommand & d);
    const SRNS_DataForwardCommand *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC ForwardSRNS_Context_PDU : public ConcretePDU {
public:
    ForwardSRNS_Context_PDU();
    void set_data(ForwardSRNS_Context &);
    ForwardSRNS_Context *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const ForwardSRNS_Context & d);
    const ForwardSRNS_Context *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_AssignmentRequest_PDU : public ConcretePDU {
public:
    RAB_AssignmentRequest_PDU();
    void set_data(RAB_AssignmentRequest &);
    RAB_AssignmentRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_AssignmentRequest & d);
    const RAB_AssignmentRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupOrModifyList_PDU : public ConcretePDU {
public:
    RAB_SetupOrModifyList_PDU();
    void set_data(RAB_SetupOrModifyList &);
    RAB_SetupOrModifyList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupOrModifyList & d);
    const RAB_SetupOrModifyList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupOrModifyItemFirst_PDU : public ConcretePDU {
public:
    RAB_SetupOrModifyItemFirst_PDU();
    void set_data(RAB_SetupOrModifyItemFirst &);
    RAB_SetupOrModifyItemFirst *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupOrModifyItemFirst & d);
    const RAB_SetupOrModifyItemFirst *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupOrModifyItemSecond_PDU : public ConcretePDU {
public:
    RAB_SetupOrModifyItemSecond_PDU();
    void set_data(RAB_SetupOrModifyItemSecond &);
    RAB_SetupOrModifyItemSecond *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupOrModifyItemSecond & d);
    const RAB_SetupOrModifyItemSecond *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_AssignmentResponse_PDU : public ConcretePDU {
public:
    RAB_AssignmentResponse_PDU();
    void set_data(RAB_AssignmentResponse &);
    RAB_AssignmentResponse *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_AssignmentResponse & d);
    const RAB_AssignmentResponse *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupOrModifiedList_PDU : public ConcretePDU {
public:
    RAB_SetupOrModifiedList_PDU();
    void set_data(RAB_SetupOrModifiedList &);
    RAB_SetupOrModifiedList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupOrModifiedList & d);
    const RAB_SetupOrModifiedList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_SetupOrModifiedItem_PDU : public ConcretePDU {
public:
    RAB_SetupOrModifiedItem_PDU();
    void set_data(RAB_SetupOrModifiedItem &);
    RAB_SetupOrModifiedItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_SetupOrModifiedItem & d);
    const RAB_SetupOrModifiedItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleasedList_PDU : public ConcretePDU {
public:
    RAB_ReleasedList_PDU();
    void set_data(RAB_ReleasedList &);
    RAB_ReleasedList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleasedList & d);
    const RAB_ReleasedList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleasedItem_PDU : public ConcretePDU {
public:
    RAB_ReleasedItem_PDU();
    void set_data(RAB_ReleasedItem &);
    RAB_ReleasedItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleasedItem & d);
    const RAB_ReleasedItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_QueuedList_PDU : public ConcretePDU {
public:
    RAB_QueuedList_PDU();
    void set_data(RAB_QueuedList &);
    RAB_QueuedList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_QueuedList & d);
    const RAB_QueuedList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_QueuedItem_PDU : public ConcretePDU {
public:
    RAB_QueuedItem_PDU();
    void set_data(RAB_QueuedItem &);
    RAB_QueuedItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_QueuedItem & d);
    const RAB_QueuedItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ReleaseFailedList_PDU : public ConcretePDU {
public:
    RAB_ReleaseFailedList_PDU();
    void set_data(RAB_ReleaseFailedList &);
    RAB_ReleaseFailedList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ReleaseFailedList & d);
    const RAB_ReleaseFailedList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GERAN_Iumode_RAB_FailedList_RABAssgntResponse_PDU : public ConcretePDU {
public:
    GERAN_Iumode_RAB_FailedList_RABAssgntResponse_PDU();
    void set_data(GERAN_Iumode_RAB_FailedList_RABAssgntResponse &);
    GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GERAN_Iumode_RAB_FailedList_RABAssgntResponse & d);
    const GERAN_Iumode_RAB_FailedList_RABAssgntResponse *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item_PDU : public ConcretePDU {
public:
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item_PDU();
    void set_data(GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item &);
    GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item & d);
    const GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC PrivateMessage_PDU : public ConcretePDU {
public:
    PrivateMessage_PDU();
    void set_data(PrivateMessage &);
    PrivateMessage *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const PrivateMessage & d);
    const PrivateMessage *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RANAP_RelocationInformation_PDU : public ConcretePDU {
public:
    RANAP_RelocationInformation_PDU();
    void set_data(RANAP_RelocationInformation &);
    RANAP_RelocationInformation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RANAP_RelocationInformation & d);
    const RANAP_RelocationInformation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DirectTransferInformationList_RANAP_RelocInf_PDU : public ConcretePDU {
public:
    DirectTransferInformationList_RANAP_RelocInf_PDU();
    void set_data(DirectTransferInformationList_RANAP_RelocInf &);
    DirectTransferInformationList_RANAP_RelocInf *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DirectTransferInformationList_RANAP_RelocInf & d);
    const DirectTransferInformationList_RANAP_RelocInf *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DirectTransferInformationItem_RANAP_RelocInf_PDU : public ConcretePDU {
public:
    DirectTransferInformationItem_RANAP_RelocInf_PDU();
    void set_data(DirectTransferInformationItem_RANAP_RelocInf &);
    DirectTransferInformationItem_RANAP_RelocInf *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DirectTransferInformationItem_RANAP_RelocInf & d);
    const DirectTransferInformationItem_RANAP_RelocInf *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ContextList_RANAP_RelocInf_PDU : public ConcretePDU {
public:
    RAB_ContextList_RANAP_RelocInf_PDU();
    void set_data(RAB_ContextList_RANAP_RelocInf &);
    RAB_ContextList_RANAP_RelocInf *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ContextList_RANAP_RelocInf & d);
    const RAB_ContextList_RANAP_RelocInf *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ContextItem_RANAP_RelocInf_PDU : public ConcretePDU {
public:
    RAB_ContextItem_RANAP_RelocInf_PDU();
    void set_data(RAB_ContextItem_RANAP_RelocInf &);
    RAB_ContextItem_RANAP_RelocInf *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ContextItem_RANAP_RelocInf & d);
    const RAB_ContextItem_RANAP_RelocInf *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ModifyRequest_PDU : public ConcretePDU {
public:
    RAB_ModifyRequest_PDU();
    void set_data(RAB_ModifyRequest &);
    RAB_ModifyRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ModifyRequest & d);
    const RAB_ModifyRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ModifyList_PDU : public ConcretePDU {
public:
    RAB_ModifyList_PDU();
    void set_data(RAB_ModifyList &);
    RAB_ModifyList *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ModifyList & d);
    const RAB_ModifyList *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC RAB_ModifyItem_PDU : public ConcretePDU {
public:
    RAB_ModifyItem_PDU();
    void set_data(RAB_ModifyItem &);
    RAB_ModifyItem *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const RAB_ModifyItem & d);
    const RAB_ModifyItem *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationRelatedDataRequest_PDU : public ConcretePDU {
public:
    LocationRelatedDataRequest_PDU();
    void set_data(LocationRelatedDataRequest &);
    LocationRelatedDataRequest *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationRelatedDataRequest & d);
    const LocationRelatedDataRequest *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationRelatedDataResponse_PDU : public ConcretePDU {
public:
    LocationRelatedDataResponse_PDU();
    void set_data(LocationRelatedDataResponse &);
    LocationRelatedDataResponse *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationRelatedDataResponse & d);
    const LocationRelatedDataResponse *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC LocationRelatedDataFailure_PDU : public ConcretePDU {
public:
    LocationRelatedDataFailure_PDU();
    void set_data(LocationRelatedDataFailure &);
    LocationRelatedDataFailure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const LocationRelatedDataFailure & d);
    const LocationRelatedDataFailure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InformationTransferIndication_PDU : public ConcretePDU {
public:
    InformationTransferIndication_PDU();
    void set_data(InformationTransferIndication &);
    InformationTransferIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InformationTransferIndication & d);
    const InformationTransferIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InformationTransferConfirmation_PDU : public ConcretePDU {
public:
    InformationTransferConfirmation_PDU();
    void set_data(InformationTransferConfirmation &);
    InformationTransferConfirmation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InformationTransferConfirmation & d);
    const InformationTransferConfirmation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC InformationTransferFailure_PDU : public ConcretePDU {
public:
    InformationTransferFailure_PDU();
    void set_data(InformationTransferFailure &);
    InformationTransferFailure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const InformationTransferFailure & d);
    const InformationTransferFailure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UESpecificInformationIndication_PDU : public ConcretePDU {
public:
    UESpecificInformationIndication_PDU();
    void set_data(UESpecificInformationIndication &);
    UESpecificInformationIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UESpecificInformationIndication & d);
    const UESpecificInformationIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC DirectInformationTransfer_PDU : public ConcretePDU {
public:
    DirectInformationTransfer_PDU();
    void set_data(DirectInformationTransfer &);
    DirectInformationTransfer *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const DirectInformationTransfer & d);
    const DirectInformationTransfer *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UplinkInformationTransferIndication_PDU : public ConcretePDU {
public:
    UplinkInformationTransferIndication_PDU();
    void set_data(UplinkInformationTransferIndication &);
    UplinkInformationTransferIndication *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UplinkInformationTransferIndication & d);
    const UplinkInformationTransferIndication *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UplinkInformationTransferConfirmation_PDU : public ConcretePDU {
public:
    UplinkInformationTransferConfirmation_PDU();
    void set_data(UplinkInformationTransferConfirmation &);
    UplinkInformationTransferConfirmation *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UplinkInformationTransferConfirmation & d);
    const UplinkInformationTransferConfirmation *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

class OSS_PUBLIC UplinkInformationTransferFailure_PDU : public ConcretePDU {
public:
    UplinkInformationTransferFailure_PDU();
    void set_data(UplinkInformationTransferFailure &);
    UplinkInformationTransferFailure *get_data() const;
#ifdef OSS_PREALLOCATED_BUFFER_DECODE_SUPPORTED
    void set_const_data(const UplinkInformationTransferFailure & d);
    const UplinkInformationTransferFailure *get_const_data() const;
#endif
protected:
    OssTypeIndex get_index() const;
};

/* Control object class */

class OSS_PUBLIC ranap_Control : public OssControl {
public:
    ranap_Control();
    ranap_Control(const ranap_Control &);
};


/* External definitions for named values */

const OSS_INT32 id_RAB_Assignment = 0;

const OSS_INT32 id_Iu_Release = 1;

const OSS_INT32 id_RelocationPreparation = 2;

const OSS_INT32 id_RelocationResourceAllocation = 3;

const OSS_INT32 id_RelocationCancel = 4;

const OSS_INT32 id_SRNS_ContextTransfer = 5;

const OSS_INT32 id_SecurityModeControl = 6;

const OSS_INT32 id_DataVolumeReport = 7;

const OSS_INT32 id_Reset = 9;

const OSS_INT32 id_RAB_ReleaseRequest = 10;

const OSS_INT32 id_Iu_ReleaseRequest = 11;

const OSS_INT32 id_RelocationDetect = 12;

const OSS_INT32 id_RelocationComplete = 13;

const OSS_INT32 id_Paging = 14;

const OSS_INT32 id_CommonID = 15;

const OSS_INT32 id_CN_InvokeTrace = 16;

const OSS_INT32 id_LocationReportingControl = 17;

const OSS_INT32 id_LocationReport = 18;

const OSS_INT32 id_InitialUE_Message = 19;

const OSS_INT32 id_DirectTransfer = 20;

const OSS_INT32 id_OverloadControl = 21;

const OSS_INT32 id_ErrorIndication = 22;

const OSS_INT32 id_SRNS_DataForward = 23;

const OSS_INT32 id_ForwardSRNS_Context = 24;

const OSS_INT32 id_privateMessage = 25;

const OSS_INT32 id_CN_DeactivateTrace = 26;

const OSS_INT32 id_ResetResource = 27;

const OSS_INT32 id_RANAP_Relocation = 28;

const OSS_INT32 id_RAB_ModifyRequest = 29;

const OSS_INT32 id_LocationRelatedData = 30;

const OSS_INT32 id_InformationTransfer = 31;

const OSS_INT32 id_UESpecificInformation = 32;

const OSS_INT32 id_UplinkInformationTransfer = 33;

const OSS_INT32 id_DirectInformationTransfer = 34;

const OSS_INT32 maxPrivateIEs = USHRT_MAX;

const OSS_INT32 maxProtocolExtensions = USHRT_MAX;

const OSS_INT32 maxProtocolIEs = USHRT_MAX;

const OSS_INT32 maxNrOfDTs = 15;

const OSS_INT32 maxNrOfErrors = 256;

const OSS_INT32 maxNrOfIuSigConIds = 250;

const OSS_INT32 maxNrOfPDPDirections = 2;

const OSS_INT32 maxNrOfPoints = 15;

const OSS_INT32 maxNrOfRABs = 256;

const OSS_INT32 maxNrOfSeparateTrafficDirections = 2;

const OSS_INT32 maxNrOfSRBs = 8;

const OSS_INT32 maxNrOfVol = 2;

const OSS_INT32 maxNrOfLevels = 256;

const OSS_INT32 maxNrOfAltValues = 16;

const OSS_INT32 maxNrOfPLMNsSN = 32;

const OSS_INT32 maxNrOfLAs = 65536;

const OSS_INT32 maxNrOfSNAs = 65536;

const OSS_INT32 maxNrOfUEsToBeTraced = 64;

const OSS_INT32 maxNrOfInterfaces = 16;

const OSS_INT32 maxRAB_Subflows = 7;

const OSS_INT32 maxRAB_SubflowCombination = 64;

const OSS_INT32 maxSet = 9;

const OSS_INT32 id_AreaIdentity = 0;

const OSS_INT32 id_CN_DomainIndicator = 3;

const OSS_INT32 id_Cause = 4;

const OSS_INT32 id_ChosenEncryptionAlgorithm = 5;

const OSS_INT32 id_ChosenIntegrityProtectionAlgorithm = 6;

const OSS_INT32 id_ClassmarkInformation2 = 7;

const OSS_INT32 id_ClassmarkInformation3 = 8;

const OSS_INT32 id_CriticalityDiagnostics = 9;

const OSS_INT32 id_DL_GTP_PDU_SequenceNumber = 10;

const OSS_INT32 id_EncryptionInformation = 11;

const OSS_INT32 id_IntegrityProtectionInformation = 12;

const OSS_INT32 id_IuTransportAssociation = 13;

const OSS_INT32 id_L3_Information = 14;

const OSS_INT32 id_LAI = 15;

const OSS_INT32 id_NAS_PDU = 16;

const OSS_INT32 id_NonSearchingIndication = 17;

const OSS_INT32 id_NumberOfSteps = 18;

const OSS_INT32 id_OMC_ID = 19;

const OSS_INT32 id_OldBSS_ToNewBSS_Information = 20;

const OSS_INT32 id_PagingAreaID = 21;

const OSS_INT32 id_PagingCause = 22;

const OSS_INT32 id_PermanentNAS_UE_ID = 23;

const OSS_INT32 id_RAB_ContextItem = 24;

const OSS_INT32 id_RAB_ContextList = 25;

const OSS_INT32 id_RAB_DataForwardingItem = 26;

const OSS_INT32 id_RAB_DataForwardingItem_SRNS_CtxReq = 27;

const OSS_INT32 id_RAB_DataForwardingList = 28;

const OSS_INT32 id_RAB_DataForwardingList_SRNS_CtxReq = 29;

const OSS_INT32 id_RAB_DataVolumeReportItem = 30;

const OSS_INT32 id_RAB_DataVolumeReportList = 31;

const OSS_INT32 id_RAB_DataVolumeReportRequestItem = 32;

const OSS_INT32 id_RAB_DataVolumeReportRequestList = 33;

const OSS_INT32 id_RAB_FailedItem = 34;

const OSS_INT32 id_RAB_FailedList = 35;

const OSS_INT32 id_RAB_ID = 36;

const OSS_INT32 id_RAB_QueuedItem = 37;

const OSS_INT32 id_RAB_QueuedList = 38;

const OSS_INT32 id_RAB_ReleaseFailedList = 39;

const OSS_INT32 id_RAB_ReleaseItem = 40;

const OSS_INT32 id_RAB_ReleaseList = 41;

const OSS_INT32 id_RAB_ReleasedItem = 42;

const OSS_INT32 id_RAB_ReleasedList = 43;

const OSS_INT32 id_RAB_ReleasedList_IuRelComp = 44;

const OSS_INT32 id_RAB_RelocationReleaseItem = 45;

const OSS_INT32 id_RAB_RelocationReleaseList = 46;

const OSS_INT32 id_RAB_SetupItem_RelocReq = 47;

const OSS_INT32 id_RAB_SetupItem_RelocReqAck = 48;

const OSS_INT32 id_RAB_SetupList_RelocReq = 49;

const OSS_INT32 id_RAB_SetupList_RelocReqAck = 50;

const OSS_INT32 id_RAB_SetupOrModifiedItem = 51;

const OSS_INT32 id_RAB_SetupOrModifiedList = 52;

const OSS_INT32 id_RAB_SetupOrModifyItem = 53;

const OSS_INT32 id_RAB_SetupOrModifyList = 54;

const OSS_INT32 id_RAC = 55;

const OSS_INT32 id_RelocationType = 56;

const OSS_INT32 id_RequestType = 57;

const OSS_INT32 id_SAI = 58;

const OSS_INT32 id_SAPI = 59;

const OSS_INT32 id_SourceID = 60;

const OSS_INT32 id_SourceRNC_ToTargetRNC_TransparentContainer = 61;

const OSS_INT32 id_TargetID = 62;

const OSS_INT32 id_TargetRNC_ToSourceRNC_TransparentContainer = 63;

const OSS_INT32 id_TemporaryUE_ID = 64;

const OSS_INT32 id_TraceReference = 65;

const OSS_INT32 id_TraceType = 66;

const OSS_INT32 id_TransportLayerAddress = 67;

const OSS_INT32 id_TriggerID = 68;

const OSS_INT32 id_UE_ID = 69;

const OSS_INT32 id_UL_GTP_PDU_SequenceNumber = 70;

const OSS_INT32 id_RAB_FailedtoReportItem = 71;

const OSS_INT32 id_RAB_FailedtoReportList = 72;

const OSS_INT32 id_KeyStatus = 75;

const OSS_INT32 id_DRX_CycleLengthCoefficient = 76;

const OSS_INT32 id_IuSigConIdList = 77;

const OSS_INT32 id_IuSigConIdItem = 78;

const OSS_INT32 id_IuSigConId = 79;

const OSS_INT32 id_DirectTransferInformationItem_RANAP_RelocInf = 80;

const OSS_INT32 id_DirectTransferInformationList_RANAP_RelocInf = 81;

const OSS_INT32 id_RAB_ContextItem_RANAP_RelocInf = 82;

const OSS_INT32 id_RAB_ContextList_RANAP_RelocInf = 83;

const OSS_INT32 id_RAB_ContextFailedtoTransferItem = 84;

const OSS_INT32 id_RAB_ContextFailedtoTransferList = 85;

const OSS_INT32 id_GlobalRNC_ID = 86;

const OSS_INT32 id_RAB_ReleasedItem_IuRelComp = 87;

const OSS_INT32 id_MessageStructure = 88;

const OSS_INT32 id_Alt_RAB_Parameters = 89;

const OSS_INT32 id_Ass_RAB_Parameters = 90;

const OSS_INT32 id_RAB_ModifyList = 91;

const OSS_INT32 id_RAB_ModifyItem = 92;

const OSS_INT32 id_TypeOfError = 93;

const OSS_INT32 id_BroadcastAssistanceDataDecipheringKeys = 94;

const OSS_INT32 id_LocationRelatedDataRequestType = 95;

const OSS_INT32 id_GlobalCN_ID = 96;

const OSS_INT32 id_LastKnownServiceArea = 97;

const OSS_INT32 id_SRB_TrCH_Mapping = 98;

const OSS_INT32 id_InterSystemInformation_TransparentContainer = 99;

const OSS_INT32 id_NewBSS_To_OldBSS_Information = 100;

const OSS_INT32 id_SourceRNC_PDCP_context_info = 103;

const OSS_INT32 id_InformationTransferID = 104;

const OSS_INT32 id_SNA_Access_Information = 105;

const OSS_INT32 id_ProvidedData = 106;

const OSS_INT32 id_GERAN_BSC_Container = 107;

const OSS_INT32 id_GERAN_Classmark = 108;

const OSS_INT32 id_GERAN_Iumode_RAB_Failed_RABAssgntResponse_Item = 109;

const OSS_INT32 id_GERAN_Iumode_RAB_FailedList_RABAssgntResponse = 110;

const OSS_INT32 id_VerticalAccuracyCode = 111;

const OSS_INT32 id_ResponseTime = 112;

const OSS_INT32 id_PositioningPriority = 113;

const OSS_INT32 id_ClientType = 114;

const OSS_INT32 id_LocationRelatedDataRequestTypeSpecificToGERANIuMode = 115;

const OSS_INT32 id_SignallingIndication = 116;

const OSS_INT32 id_hS_DSCH_MAC_d_Flow_ID = 117;

const OSS_INT32 id_UESBI_Iu = 118;

const OSS_INT32 id_PositionData = 119;

const OSS_INT32 id_PositionDataSpecificToGERANIuMode = 120;

const OSS_INT32 id_CellLoadInformationGroup = 121;

const OSS_INT32 id_AccuracyFulfilmentIndicator = 122;

const OSS_INT32 id_InformationTransferType = 123;

const OSS_INT32 id_TraceRecordingSessionInformation = 124;

const OSS_INT32 id_TracePropagationParameters = 125;

const OSS_INT32 id_InterSystemInformationTransferType = 126;

extern OSS_PUBLIC const RANAP_PDU& value;

#endif // OSS_ranap
