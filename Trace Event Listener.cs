namespace Microsoft.Diagnostics.Tracing.Parsers.AspNet
{
    public sealed class AspNetStartTraceData : TraceEvent
    {
        public long ConnId { get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }
        public string Method { get { return GetUTF8StringAt(24); } }
        public string Path { get { return GetUTF8StringAt(SkipUTF8String(24)); } }
        public string QueryString { get { return GetUTF8StringAt(SkipUTF8String(SkipUTF8String(24))); } }

        #region private 
        internal AspNetStartTraceData(Action<AspNetStartTraceData> action, int eventId, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, Guid providerGuid, string providerName)
        : base(eventId, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
            action(this);
        }
        protected internal override Delegate Target
        {
            get { return Action; }
            set { Action = (Action<AspNetStartTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != SkipUTF8String(SkipUTF8String(24))) && EventDataLength != 8);
            Debug.Assert(!(Version > 0 && EventDataLength < SkipUTF8String(SkipUTF8String(24))));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextID", ContextId);
            XmlAttrib(sb, "Method", Method);
            XmlAttrib(sb, "Path", Path);
            XmlAttrib(sb, "QueryString", QueryString);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames()
        {
            get 
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId", "Method", "Path", "QueryString" };
                }
                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                     return ConnID;
                case 1:
                     return ContextId;
                case 2:
                     return Method;
                case 3:
                     return Path;
                case 4:
                     return QueryString;
                default:
                     Debug.Assert(false, "Bad field index");
                     return null;
            }
        }

        private event Action<AspNetStartTraceData> Action;
        #endregion
    }
    public sealed class AspNetStopTraceData : TraceEvent
    {
        public long ConnID {get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }

        #region Private
        internal AspNetStopTraceData(Action<AspNetStopTraceData> action, int eventId, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, Guid providerGuid, string providerName)
        : base(eventId, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
            Action(this);
        }
        protected internal override Delegate Target 
        {
            get { return Action; }
            set { Action = (Action<AspNetStartTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != 24 && EventDataLength != 8));
            Debug.Assert(!(Version > 0 && EventDataLength < 24));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextId", ContextId);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames()
        {
            get 
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId" };
                }

                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                     return ConnID;
                case 1:
                     return ContextId;
                case 2:
                     return Method;
                case 3:
                     return Path;
                case 4:
                     return QueryString;
                default:
                     Debug.Assert(false, "Bad field index");
                     return null;
            }
        }

        private event Action<AspNetStopTraceData> Action;
        #endregion
    }
    public sealed class AspNetRequestQueuedTraceData : TraceEvent
    {
        public long ConnID { get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }

        #region private 
        internal AspNetRequestQueuedTraceData(Action<AspNetRequestQueuedTraceData> action, int eventId, int task, string taskName, Guid taskGuid, int opcode, int opcodeName, Guid providerGuid, string providerName)
        : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
           Action(this); 
        }
        protected internal override Delegate Target 
        {
            get { return Action; }
            set { Action = (Action<AspNetRequestQueuedTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != 24));
            Debug.Assert(!(Version > 0 && EventDataLength < 24));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextId", ContextId);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames()
        {
            get
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId" };
                }

                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                     return ConnID;
                case 1:
                     return ContextId;
                case 2:
                     return Method;
                case 3:
                     return Path;
                case 4:
                     return QueryString;
                default:
                     Debug.Assert("Error while indexing the result")
                     return null;
            }
        }

        private event Action<AspNetRequestQueuedTraceData> Action;
        #endregion
    }
    public sealed class AspNetRequestDequeuedTraceData : TraceEvent
    {
        public long ConnID { get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }

        #region Private
        internal AspNetRequestDequeuedTraceData(Action<AspNetRequestDequeuedTraceData> action, int eventID, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, int providerGuid, string providerName)
        : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
            Action(this);
        }
        protected internal override void Validate()
        {
            get { return Action; }
            set { Action = (Action<AspNetRequestDequeuedTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != 24));
            Debug.Assert(!(Version > 0 && EventDataLength < 24));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextId", ContextId);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames
        {
            get
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId" };
                }

                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                    return ConnID;
                case 1:
                    return ContextId;
                default:
                    Debug.Assert(false, "Error of indexing");
                    return null;
            }
        }

        private event Action<AspNetRequestDequeuedTraceData> Action;
        #endregion
    }
    public sealed class AspNetGetAppDomainEnterTraceData : TraceEvent
    {
        public long ConnID { get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }

        #region Private
        internal AspNetRequestDequeuedTraceData(Action<AspNetRequestGetAppDomainEnterTraceData> action, int eventID, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, int providerGuid, string providerName)
        : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
            Action(this);
        }
        protected internal override void Validate()
        {
            get { return Action; }
            set { Action = (Action<AspNetRequestGetAppDomainEnterTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != 24));
            Debug.Assert(!(Version > 0 && EventDataLength < 24));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextId", ContextId);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames
        {
            get
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId" };
                }

                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                    return ConnID;
                case 1:
                    return ContextId;
                default:
                    Debug.Assert(false, "Error of indexing");
                    return null;
            }
        }

        private event Action<AspNetRequestGetAppDomainEnterTraceData> Action;
        #endregion
    }

    public long ConnID { get { return GetInt64At(0); } }
        public Guid ContextId { get { return GetGuidAt(8); } }

        #region Private
        internal AspNetRequestDequeuedTraceData(Action<AspNetRequestLeaveTraceData> action, int eventID, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, int providerGuid, string providerName)
        : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
        {
            Action = action;
        }
        protected internal override void Dispatch()
        {
            Action(this);
        }
        protected internal override void Validate()
        {
            get { return Action; }
            set { Action = (Action<AspNetRequestLeaveTraceData>)value; }
        }
        protected internal override void Validate()
        {
            Debug.Assert(!(Version == 0 && EventDataLength != 24));
            Debug.Assert(!(Version > 0 && EventDataLength < 24));
        }
        public override StringBuilder ToXml(StringBuilder sb)
        {
            Prefix(sb);
            XmlAttrib(sb, "ConnID", ConnID);
            XmlAttrib(sb, "ContextId", ContextId);
            sb.Append("/>");
            return sb;
        }

        public override string[] PayloadNames
        {
            get
            {
                if (PayloadNames == null)
                {
                    PayloadNames = new string[] { "ConnID", "ContextId" };
                }

                return PayloadNames;
            }
        }

        public override object PayloadValue(int index)
        {
            switch (index)
            {
                case 0:
                    return ConnID;
                case 1:
                    return ContextId;
                default:
                    Debug.Assert(false, "Error of indexing");
                    return null;
            }
        }

        private event Action<AspNetRequestLeaveTraceData> Action;
        #endregion
    }
public sealed class AspNetAppDomainEnterTraceData : TraceEvent
{
    public long ConnID { get { return GetInt64At(0); } }
    public Guid ContextId { get { return GetInt64At(8); } }
    public strign DomainId { get { return GetUnicodeStringAt(24); } }

    #region Private
    internal AspNetAppDomainEnterTraceData(Action<AspNetAppDomainEnterTraceData> action, int eventID, int task, string taskName, Guid taskGuid, int opcode, string opcodeName, int providerGuid, string providerName)
    : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
    {
        Action = action;
    }
    protected internal override void Dispatch()
    {
        Action(this);
    }
    protected internal override Delegate Target 
    {
        get { return Action; }
        set { Action = (Action<AspNetAppDomainEnterTraceData>)value; }
    }
    protected internal override void Validate()
    {
        Debug.Assert(!(Version == 0 && EventDataLength != SkipUnicodeString(24)));
        Debug.Assert(!(Version > 0 && EventDataLength < SkipUnicodeString(24)));
    }
    public override StringBuilder ToXml(StringBuilder sb)
    {
        Prefix(sb);
        XmlAttrib(sb, "ConnID", ConnID);
        XmlAttrib(sb, "ContextId", ContextId);
        XmlAttrib(sb, "DomainId", DomainId);
        sb.Append("/>");
        return sb;
    }

    public override string[] PayloadNames
    {
        get
        {
            if (PayloadNames == null)
            {
                PayloadNames = new string[] { "ConnID", "ContextId", "DomaindId" };
            }

            return PayloadNames;
        }
    }

    public override object PayloadValue(int index)
    {
        switch (index)
        {
            case 0:
                return ConnID;
            case 1:
                return ContextId;
            case 2:
                return DomaindId;
            default;
                Debug.Assert(false, "Error of indexing");
                return null;
        }
    }

    private event Action<AspNetAppDomainEnterTraceData> Action;
    #endregion
}
public sealed class AspNetStartHandlerTraceData : TraceEvent
{
    public long ConnID { get { return GetInt64At(0); } }
    public long ContextId { get { return GetInt64At(8); } }
    public string HandlerName { get { return GetUnicodeStringAt(24); } }
    public new string EventName { get { return GetUnicodeStringAt(SkipUnicodeString(24)); } }

    #region Private
    internal AspNetStartHandlerTraceData(Action<AspNetAppDomainEnterTraceData> action, int eventID, int task, string taskName, Guid taskGuid, int providerGuid, string providerName)
    : base(eventID, task, taskName, taskGuid, opcode, opcodeName, providerGuid, providerName)
    {
        Action = action;
    }
    protected internal override void Dispatch()
    {
        Action(this);
    }
    protected internal override Delegate Target
    {
        get { return Action; }
        set { Action = (Action<AspNetAppDomainEnterTraceData>)value; }
    }
    protected internal override void Validate()
    {
        Debug.Assert(!(Version == 0 && EventDataLength != SkipUnicodeString(SkipUnicodeString(24))));
        Debug.Assert(!(Version > 0 && EventDataLength < SkipUnicodeString(SkipUnicodeString(24))));
    }
    public override StringBuilder ToXml(StringBuilder sb)
    {
        Prefix(sb);
        XmlAttrib(sb, "ConnID", ConnID);
        XmlAttrib(sb, "ContextId", ContextId);
        XmlAttrib(sb, "HandlerName", HandlerName);
        XmlAttrib(sb, "EventName", EventName);
        sb.Append("/>");
        return sb;
    }

    public override string[] PayloadNames
    {
        get
        {
            if (PayloadNames == null)
            {
                PayloadNames = new string[] { "ConnID", "ContextId", "HandlerName", "EventName" };
            }

            return PayloadNames;
        }
    }

    public override object PayloadValue(int index)
    {
        switch (index)
        {
            case 0:
                return ConnID;
            case 1:
                return ContextId;
            case 2:
                return HandlerName;
            case 3:
                return EventName;
            default:
                Debug.Assert(false, "Error indexing");
                return null;
        }
    }

    private event Action<AspNetAppDomainEnterTraceData> Action;
    #endregion
}
