/**
 * UGENE - Integrated Bioinformatics Tools.
 * Copyright (C) 2008-2019 UniPro <ugene@unipro.ru>
 * http://ugene.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

#include <U2Core/BaseDocumentFormats.h>

#include <U2Lang/BaseTypes.h>
#include <U2Lang/ExternalToolCfg.h>

namespace U2 {

const DocumentFormatId DataConfig::STRING_VALUE = DocumentFormatId("string-value");
const DocumentFormatId DataConfig::OUTPUT_FILE_URL = DocumentFormatId("output-file-url");

bool DataConfig::isStringValue() const {
    return (BaseTypes::STRING_TYPE()->getId() == type) && (STRING_VALUE == format);
}

bool DataConfig::isFileUrl() const {
    return (OUTPUT_FILE_URL == format);
}

bool DataConfig::isSequence() const {
    return (BaseTypes::DNA_SEQUENCE_TYPE()->getId() == type);
}

bool DataConfig::isAnnotations() const {
    return (BaseTypes::ANNOTATION_TABLE_TYPE()->getId() == type);
}

bool DataConfig::isAnnotatedSequence() const {
    return (SEQ_WITH_ANNS == type);
}

bool DataConfig::isAlignment() const {
    return (BaseTypes::MULTIPLE_ALIGNMENT_TYPE()->getId() == type);
}

bool DataConfig::isText() const {
    return (BaseTypes::STRING_TYPE()->getId() == type) && (BaseDocumentFormats::PLAIN_TEXT == format);
}

bool DataConfig::operator ==(const DataConfig &other) const {
    return attributeId == other.attributeId
            && attrName == other.attrName
            && type == other.type
            && format == other.format
            && description == other.description;
}

bool AttributeConfig::operator ==(const AttributeConfig &other) const {
    return attributeId == other.attributeId
            && attrName == other.attrName
            && type == other.type
            && defaultValue == other.defaultValue
            && description == other.description;
}

ExternalProcessConfig::ExternalProcessConfig()
    : useIntegratedTool(false)
{

}

#define CHECK_EQ(expr1, expr2) \
    if (!(expr1 == expr2)) {\
    return false;\
    }

bool ExternalProcessConfig::operator ==(const ExternalProcessConfig &other) const {
    CHECK_EQ(inputs.size(), other.inputs.size());
    CHECK_EQ(outputs.size(), other.outputs.size());
    CHECK_EQ(attrs.size(), other.attrs.size());
    CHECK_EQ(id, other.id);
    CHECK_EQ(name, other.name);
    CHECK_EQ(description, other.description);
    CHECK_EQ(useIntegratedTool, other.useIntegratedTool);
    CHECK_EQ(customToolPath, other.customToolPath);
    CHECK_EQ(integratedToolId, other.integratedToolId);

    foreach (const DataConfig &in, inputs) {
        CHECK_EQ(other.inputs.contains(in), true);
    }
    foreach (const DataConfig &out, outputs) {
        CHECK_EQ(other.outputs.contains(out), true);
    }
    foreach (const AttributeConfig &at, attrs) {
        CHECK_EQ(other.attrs.contains(at), true);
    }

    return true;
}

bool ExternalProcessConfig::operator !=(const ExternalProcessConfig &other) const {
    return !operator==(other);
}

ExternalToolCfgRegistry::ExternalToolCfgRegistry(QObject *_parent)
    : QObject(_parent)
{

}

bool ExternalToolCfgRegistry::registerExternalTool(ExternalProcessConfig *cfg) {
    if (configs.contains(cfg->id)) {
        return false;
    } else {
        configs.insert(cfg->id, cfg);
        return true;
    }
}

void ExternalToolCfgRegistry::unregisterConfig(const QString &id) {
    // TODO: UTI-294
    configs.remove(id);
}

ExternalProcessConfig *ExternalToolCfgRegistry::getConfigById(const QString &id) const {
    return configs.value(id, nullptr);
}

QList<ExternalProcessConfig *> ExternalToolCfgRegistry::getConfigs() const {
    return configs.values();
}

} // U2
