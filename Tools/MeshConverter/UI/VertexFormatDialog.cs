using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MeshConverter.TriangleMesh.VertexLayout;

namespace MeshConverter.UI
{
    public partial class VertexFormatDialog : Form
    {
        public VertexFormatDialog()
        {
            InitializeComponent();

            m_formats_ = null;
        }

        public string SemanticName
        {
            get
            {
                return m_semantic_name_text_box_.Text;
            }
            set
            {
                m_semantic_name_text_box_.Text = value;
            }
        }

        public int SemanticIndex
        {
            get
            {
                if (m_semantic_index_numeric_up_down_.Enabled)
                {
                    return (int)m_semantic_index_numeric_up_down_.Value;
                }
                else
                {
                    return m_semantic_index_;
                }
            }
            set
            {
                if(value >= 0)
                {
                    m_semantic_index_numeric_up_down_.Enabled = true;
                    m_semantic_index_numeric_up_down_.Value = value;
                    m_semantic_index_ = value;
                }
                else
                {
                    m_semantic_index_numeric_up_down_.Enabled = false;
                    m_semantic_index_numeric_up_down_.Value = 0;
                    m_semantic_index_ = value;
                }
            }
        }

        public LayoutEntryFormat[] Formats
        {
            get
            {
                return m_formats_;
            }
            set
            {
                m_formats_ = value;

                m_format_combobox_.Items.Clear();
                for (int index = 0; index < m_formats_.Length; ++index)
                {
                    m_format_combobox_.Items.Add(m_formats_[index].ToString());
                }

                m_format_combobox_.SelectedIndex = 0;
            }
        }

        public LayoutEntryFormat DefaultFormat
        {
            get;
            set;
        }

        public LayoutEntryFormat SelectedFormat
        {
            get
            {
                return m_formats_[m_format_combobox_.SelectedIndex];
            }
            set
            {
                m_format_combobox_.SelectedIndex = Array.IndexOf<LayoutEntryFormat>(m_formats_, value);
            }
        }

        private void m_defaults_button__Click(object sender, EventArgs e)
        {
            SelectedFormat = DefaultFormat;
        }

        private int m_semantic_index_;
        private LayoutEntryFormat[] m_formats_;
    }
}
