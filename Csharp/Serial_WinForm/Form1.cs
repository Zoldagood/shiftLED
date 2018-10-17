using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.IO.Ports;
using System.Linq;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace Serial_WinForm
{
    public partial class Form1 : Form
    {
        String[] baudrate;
        String[] comports;
        public Form1()
        {
            InitializeComponent();
            IsSerialSts();
            try {
                
                comports = SerialPort.GetPortNames();
                baudrate = new String[] { "9600", "115200" };
                BaudRate_comboBox.Items.AddRange(baudrate);
                Device_comboBox.Items.AddRange(comports);

            }
            catch(Exception)
            {
                richTextBox1.AppendText("설정을 확인하세요\n");
            }

        }
        private void IsSerialSts()
        {
            if (serialPort1.IsOpen)
            {
                Open.Enabled = false;
                Close.Enabled = true;
               
            }
            else
            {
                Open.Enabled = true;
                Close.Enabled = false;
               
            }
        }
           
       

        private void Form1_Load(object sender, EventArgs e)
        {
            
        }

        private void Open_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.PortName = Device_comboBox.SelectedItem.ToString();
                serialPort1.BaudRate = int.Parse(BaudRate_comboBox.SelectedItem.ToString());
                serialPort1.Open();
                IsSerialSts();
            }
            catch(Exception)
            {
                richTextBox1.AppendText("설정을 확인하세요\n");
            }

        }

        private void Close_Click(object sender, EventArgs e)
        {
            serialPort1.Close();
            IsSerialSts();

        }
        private void button1_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.WriteLine("1");
                richTextBox1.ScrollToCaret();
            }
            catch(Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n"); 
            }
               

        }

        private void button2_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("2");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button3_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("3");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button4_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("4");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button5_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("5");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button6_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("6");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button7_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("7");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void button8_Click(object sender, EventArgs e)
        {
            try { 
            serialPort1.WriteLine("8");
            richTextBox1.ScrollToCaret();
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void Clear_Click(object sender, EventArgs e)
        {
            richTextBox1.Clear();
        }

        private void Send_Click(object sender, EventArgs e)
        {
            try
            {
                serialPort1.WriteLine(textBox1.Text);
            }
            catch(Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void textBox1_KeyPress(object sender, KeyPressEventArgs e)
        {
            try
            {
                if (e.KeyChar == '\r')
                {
                    serialPort1.WriteLine(textBox1.Text);
                }
            }
            catch (Exception)
            {
                richTextBox1.AppendText("포트가 닫혀있습니다.\n");
            }
        }

        private void serialPort1_DataReceived(object sender, SerialDataReceivedEventArgs e)
        {
            try
            {
                string getdata;
                getdata = serialPort1.ReadLine();
                richTextBox1.AppendText(getdata);
                richTextBox1.ScrollToCaret();
            }
            catch(Exception)
            {

            }
        }
    }
}
