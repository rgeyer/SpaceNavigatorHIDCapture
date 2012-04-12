﻿//------------------------------------------------------------------------------
// <auto-generated>
//     This code was generated by a tool.
//     Runtime Version:2.0.50727.42
//
//     Changes to this file may cause incorrect behavior and will be lost if
//     the code is regenerated.
// </auto-generated>
//------------------------------------------------------------------------------

using System.Xml.Serialization;
using System.ComponentModel;
using System.Windows.Forms;
using System.Reflection;
using System;
using System.Collections.Generic;

// 
// This source code was auto-generated by xsd, Version=2.0.50727.42.
// 


/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
[System.Xml.Serialization.XmlRootAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/", IsNullable=false)]
public partial class snConfig {
    
    private devices devicesField;
    
    private System.Collections.Generic.List<deviceContext> deviceContextsField = new List<deviceContext>();
    
    private System.Collections.Generic.List<context> contextsField = new List<context>();
    
    private actions actionsField;
    
    private ushort gestureTimeVarianceField;
    
    private bool gestureTimeVarianceFieldSpecified;
    
    /// <remarks/>
    [System.ComponentModel.Browsable(false)]
    public devices devices {
        get {
            return this.devicesField;
        }
        set {
            this.devicesField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayItemAttribute(IsNullable=false)]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<deviceContext> deviceContexts
    {
        get {
            return this.deviceContextsField;
        }
        set {
            this.deviceContextsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayItemAttribute(IsNullable=false)]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<context> contexts
    {
        get {
            return this.contextsField;
        }
        set {
            this.contextsField = value;
        }
    }
    
    /// <remarks/>
    [System.ComponentModel.Browsable(false)]
    public actions actions {
        get {
            return this.actionsField;
        }
        set {
            this.actionsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort gestureTimeVariance {
        get {
            return this.gestureTimeVarianceField;
        }
        set {
            this.gestureTimeVarianceField = value;
            this.gestureTimeVarianceFieldSpecified = true;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool gestureTimeVarianceSpecified {
        get {
            return this.gestureTimeVarianceFieldSpecified;
        }
        set {
            this.gestureTimeVarianceFieldSpecified = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class devices {
    
    private System.Collections.Generic.List<device> itemsField = new List<device>();
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("hid", typeof(hidDevice))]
    [System.Xml.Serialization.XmlElementAttribute("mouse", typeof(device))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<device> Items
    {
        get {
            return this.itemsField;
        }
        set {
            this.itemsField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class hidDevice : device {
    
    private System.Collections.Generic.List<hidCommand> commandField = new List<hidCommand>();
    
    private string vidField;
    
    private string pidField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("command", typeof(hidCommand))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<hidCommand> command
    {
        get {
            return this.commandField;
        }
        set {
            this.commandField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="integer")]
    public string vid {
        get {
            return this.vidField;
        }
        set {
            this.vidField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="integer")]
    public string pid {
        get {
            return this.pidField;
        }
        set {
            this.pidField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class hidCommand {
    
    private string nameField;
    
    private string reportField;
    
    private string valueField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="integer")]
    public string report {
        get {
            return this.reportField;
        }
        set {
            this.reportField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute(DataType="integer")]
    public string value {
        get {
            return this.valueField;
        }
        set {
            this.valueField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class macro {
    
    private System.Collections.Generic.List<action> actionField = new System.Collections.Generic.List<action>();
    
    private string nameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("action", typeof(action))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<action> action
    {
        get {
            return this.actionField;
        }
        set {
            this.actionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace = "https://sourceforge.net/projects/spacenavdrvr/")]
public partial class action
{

    private string nameField;

    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string name
    {
        get
        {
            return this.nameField;
        }
        set
        {
            this.nameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class keyPress {
    
    private System.Collections.Generic.List<key> keyField = new System.Collections.Generic.List<key>();
    
    private string nameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("key", typeof(key))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<key> key
    {
        get {
            return this.keyField;
        }
        set {
            this.keyField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType = true)]
public partial class key {

    private ushort keyCodeField;

    private bool keyCodeFieldSpecified;

    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort keyCode
    {
        get
        {
            return this.keyCodeField;
        }
        set
        {
            this.keyCodeField = value;
            this.keyCodeFieldSpecified = true;
        }
    }

    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool keyCodeSpecified
    {
        get
        {
            return this.keyCodeFieldSpecified;
        }
        set
        {
            this.keyCodeFieldSpecified = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class execute {
    
    private string nameField;
    
    private string executableField;
    
    private string commandlineField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string executable {
        get {
            return this.executableField;
        }
        set {
            this.executableField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string commandline {
        get {
            return this.commandlineField;
        }
        set {
            this.commandlineField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class sendCommandWindowMessage {
    
    private string nameField;
    
    private string windowField;
    
    private string windowClassField;
    
    private uint messageField;
    
    public string type
    {
        get { return this.GetType().ToString(); }
    }

    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string window {
        get {
            return this.windowField;
        }
        set {
            this.windowField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string windowClass {
        get {
            return this.windowClassField;
        }
        set {
            this.windowClassField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public uint message {
        get {
            return this.messageField;
        }
        set {
            this.messageField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class sendCopyDataWindowMessage {
    
    private string nameField;
    
    private string windowField;
    
    private string windowClassField;
    
    private string messageField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string window {
        get {
            return this.windowField;
        }
        set {
            this.windowField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string windowClass {
        get {
            return this.windowClassField;
        }
        set {
            this.windowClassField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string message {
        get {
            return this.messageField;
        }
        set {
            this.messageField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class actions {
    
    private System.Collections.Generic.List<object> itemsField = new List<object>();
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("execute", typeof(execute))]
    [System.Xml.Serialization.XmlElementAttribute("keyPress", typeof(keyPress))]
    [System.Xml.Serialization.XmlElementAttribute("macro", typeof(macro))]
    [System.Xml.Serialization.XmlElementAttribute("sendCommandWindowMessage", typeof(sendCommandWindowMessage))]
    [System.Xml.Serialization.XmlElementAttribute("sendCopyDataWindowMessage", typeof(sendCopyDataWindowMessage))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<object> Items
    {
        get {
            return this.itemsField;
        }
        set {
            this.itemsField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class context {
    
    private string nameField;
    
    private string deviceContextField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(DeviceContextTypeConverter))]
    public string deviceContext {
        get {
            return this.deviceContextField;
        }
        set {
            this.deviceContextField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class wait {
    
    private ushort lengthField;
    
    private bool lengthFieldSpecified;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort length {
        get {
            return this.lengthField;
        }
        set {
            this.lengthField = value;
            this.lengthFieldSpecified = true;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool lengthSpecified {
        get {
            return this.lengthFieldSpecified;
        }
        set {
            this.lengthFieldSpecified = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class motion {
    
    private motionPosition positionField;
    
    private bool positionFieldSpecified;
    
    private ushort axeField;
    
    private bool axeFieldSpecified;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public motionPosition position {
        get {
            return this.positionField;
        }
        set {
            this.positionField = value;
            this.positionFieldSpecified = true;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool positionSpecified {
        get {
            return this.positionFieldSpecified;
        }
        set {
            this.positionFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort axe {
        get {
            return this.axeField;
        }
        set {
            this.axeField = value;
            this.axeFieldSpecified = true;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool axeSpecified {
        get {
            return this.axeFieldSpecified;
        }
        set {
            this.axeFieldSpecified = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public enum motionPosition {
    
    /// <remarks/>
    positive,
    
    /// <remarks/>
    center,
    
    /// <remarks/>
    negative,
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class gesture {
    
    private System.Collections.Generic.List<object> itemsField = new List<object>();

    private String actionField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("motion", typeof(motion))]
    [System.Xml.Serialization.XmlElementAttribute("wait", typeof(wait))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<object> Items
    {
        get {
            return this.itemsField;
        }
        set {
            this.itemsField = value;
        }
    }

    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string action
    {
        get
        {
            return this.actionField;
        }
        set
        {
            this.actionField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class button {
    
    private buttonSimulateMouseButton simulateMouseButtonField;
    
    private bool simulateMouseButtonFieldSpecified;
    
    private string upActionField = String.Empty;
    
    private string downActionField = String.Empty;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public buttonSimulateMouseButton simulateMouseButton {
        get {
            return this.simulateMouseButtonField;
        }
        set {
            this.simulateMouseButtonField = value;
            if (value == buttonSimulateMouseButton.none)
                this.simulateMouseButtonFieldSpecified = false;
            else
                this.simulateMouseButtonFieldSpecified = true;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool simulateMouseButtonSpecified {
        get {
            return this.simulateMouseButtonFieldSpecified;
        }
        set {
            this.simulateMouseButtonFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string upAction {
        get {
            return this.upActionField;
        }
        set {
            this.upActionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string downAction {
        get {
            return this.downActionField;
        }
        set {
            this.downActionField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public enum buttonSimulateMouseButton {
    /// <remarks/>
    none,
    
    /// <remarks/>
    left,
    
    /// <remarks/>
    right,
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class axe {
    
    private axeSimulateMouseMove simulateMouseMoveField;
    
    private bool simulateMouseMoveFieldSpecified;
    
    private ushort thresholdField;
    
    private ushort divisorField;
    
    private bool divisorFieldSpecified;
    
    private axeType typeField;
    
    private bool typeFieldSpecified;
    
    private ushort startPulseField;
    
    private bool startPulseFieldSpecified;
    
    private ushort endPulseField;
    
    private bool endPulseFieldSpecified;
    
    private string posActionField;
    
    private string negActionField;
    
    private string sendCenterField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public axeSimulateMouseMove simulateMouseMove {
        get {
            return this.simulateMouseMoveField;
        }
        set {
            this.simulateMouseMoveField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool simulateMouseMoveSpecified {
        get {
            return this.simulateMouseMoveFieldSpecified;
        }
        set {
            this.simulateMouseMoveFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort threshold {
        get {
            return this.thresholdField;
        }
        set {
            this.thresholdField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort divisor {
        get {
            return this.divisorField;
        }
        set {
            this.divisorField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool divisorSpecified {
        get {
            return this.divisorFieldSpecified;
        }
        set {
            this.divisorFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public axeType type {
        get {
            return this.typeField;
        }
        set {
            this.typeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool typeSpecified {
        get {
            return this.typeFieldSpecified;
        }
        set {
            this.typeFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort startPulse {
        get {
            return this.startPulseField;
        }
        set {
            this.startPulseField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool startPulseSpecified {
        get {
            return this.startPulseFieldSpecified;
        }
        set {
            this.startPulseFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public ushort endPulse {
        get {
            return this.endPulseField;
        }
        set {
            this.endPulseField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool endPulseSpecified {
        get {
            return this.endPulseFieldSpecified;
        }
        set {
            this.endPulseFieldSpecified = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string posAction {
        get {
            return this.posActionField;
        }
        set {
            this.posActionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(ActionTypeConverter))]
    public string negAction {
        get {
            return this.negActionField;
        }
        set {
            this.negActionField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string sendCenter {
        get {
            return this.sendCenterField;
        }
        set {
            this.sendCenterField = value;
        }
    }
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public enum axeSimulateMouseMove {
    
    /// <remarks/>
    x,
    
    /// <remarks/>
    y,
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Xml.Serialization.XmlTypeAttribute(AnonymousType=true)]
public enum axeType {
    
    /// <remarks/>
    binary,
    
    /// <remarks/>
    linear,
    
    /// <remarks/>
    exponential,
}

/// <remarks/>
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class deviceContext {
    
    private System.Collections.Generic.List<axe> axeField = new List<axe>();
    
    private System.Collections.Generic.List<button> buttonsField = new List<button>();
    
    private System.Collections.Generic.List<gesture> gestureField = new List<gesture>();
    
    private string nameField;
    
    private string deviceField;
    
    private bool gesturesField;
    
    private bool gesturesFieldSpecified;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("axe", typeof(axe))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<axe> axe {
        get {
            return this.axeField;
        }
        set {
            this.axeField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlArrayItemAttribute(IsNullable = false)]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<button> buttons {
        get {
            return this.buttonsField;
        }
        set {
            this.buttonsField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlElementAttribute("gesture", typeof(gesture))]
    [System.ComponentModel.Browsable(false)]
    public System.Collections.Generic.List<gesture> gesture {
        get {
            return this.gestureField;
        }
        set {
            this.gestureField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [TypeConverter(typeof(DeviceTypeConverter))]
    public string device {
        get {
            return this.deviceField;
        }
        set {
            this.deviceField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    [System.ComponentModel.Browsable(false)]
    public bool gestures {
        get {
            return this.gesturesField;
        }
        set {
            this.gesturesField = value;
        }
    }
    
    /// <remarks/>
    [System.Xml.Serialization.XmlIgnoreAttribute()]
    public bool gesturesSpecified {
        get {
            return this.gesturesFieldSpecified;
        }
        set {
            this.gesturesFieldSpecified = value;
        }
    }
}

/// <remarks/>
[System.Xml.Serialization.XmlIncludeAttribute(typeof(hidDevice))]
[System.CodeDom.Compiler.GeneratedCodeAttribute("xsd", "2.0.50727.42")]
[System.SerializableAttribute()]
[System.Diagnostics.DebuggerStepThroughAttribute()]
[System.ComponentModel.DesignerCategoryAttribute("code")]
[System.Xml.Serialization.XmlTypeAttribute(Namespace="https://sourceforge.net/projects/spacenavdrvr/")]
public partial class device {
    
    private string nameField;
    
    /// <remarks/>
    [System.Xml.Serialization.XmlAttributeAttribute()]
    public string name {
        get {
            return this.nameField;
        }
        set {
            this.nameField = value;
        }
    }
}


#region TypeConverters
public class ActionTypeConverter : StringConverter
{
    public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
    {
        return true;
    }
    
    public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
    {
        return true;
    }
    
    public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
    {
        PropertyInfo propInfo = context.GetType().GetProperty("OwnerGrid");
        PropertyGrid propGrid = propInfo.GetValue(context, null) as PropertyGrid;
        snConfig snConfig = propGrid.Tag as snConfig;
        List<String> retVal = new List<String>();
        foreach (object action in snConfig.actions.Items)
        {
            PropertyInfo namePropertyInfo = action.GetType().GetProperty("name");
            String name = namePropertyInfo.GetValue(action, null) as String;
            retVal.Add(name);
        }
        return new StandardValuesCollection(retVal);
    }
}

public class DeviceTypeConverter : StringConverter
{
    public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
    {
        return true;
    }

    public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
    {
        return true;
    }

    public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
    {
        PropertyInfo propInfo = context.GetType().GetProperty("OwnerGrid");
        PropertyGrid propGrid = propInfo.GetValue(context, null) as PropertyGrid;
        snConfig snConfig = propGrid.Tag as snConfig;
        List<String> retVal = new List<String>();
        foreach (object action in snConfig.devices.Items)
        {
            PropertyInfo namePropertyInfo = action.GetType().GetProperty("name");
            String name = namePropertyInfo.GetValue(action, null) as String;
            retVal.Add(name);
        }
        return new StandardValuesCollection(retVal);
    }
}

public class DeviceContextTypeConverter : StringConverter
{
    public override bool GetStandardValuesSupported(ITypeDescriptorContext context)
    {
        return true;
    }

    public override bool GetStandardValuesExclusive(ITypeDescriptorContext context)
    {
        return true;
    }

    public override StandardValuesCollection GetStandardValues(ITypeDescriptorContext context)
    {
        PropertyInfo propInfo = context.GetType().GetProperty("OwnerGrid");
        PropertyGrid propGrid = propInfo.GetValue(context, null) as PropertyGrid;
        snConfig snConfig = propGrid.Tag as snConfig;
        List<String> retVal = new List<String>();
        foreach (object action in snConfig.deviceContexts)
        {
            PropertyInfo namePropertyInfo = action.GetType().GetProperty("name");
            String name = namePropertyInfo.GetValue(action, null) as String;
            retVal.Add(name);
        }
        return new StandardValuesCollection(retVal);
    }
}
#endregion