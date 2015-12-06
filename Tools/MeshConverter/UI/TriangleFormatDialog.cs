using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using MeshConverter.TriangleMesh.TriangleLayout;

namespace MeshConverter.UI
{
    public partial class TriangleFormatDialog : Form
    {
        public TriangleFormatDialog()
        {
            InitializeComponent();
        }

        public TriangleIndexFormat[] Formats
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

        public TriangleIndexFormat DefaultFormat
        {
            get;
            set;
        }

        public TriangleIndexFormat SelectedFormat
        {
            get
            {
                return m_formats_[m_format_combobox_.SelectedIndex];
            }
            set
            {
                m_format_combobox_.SelectedIndex = Array.IndexOf<TriangleIndexFormat>(m_formats_, value);
            }
        }

        private void m_defaults_button__Click(object sender, EventArgs e)
        {
            SelectedFormat = DefaultFormat;
        }

        private TriangleIndexFormat[] m_formats_;
    }
}
