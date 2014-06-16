using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;

namespace Clientclient
{
    public partial class Form1 : Form
    {

        internal static int friend = 1;
        public delegate void ListChangedHandler(List<Sender> Clients);
        public Form1()
        {
            InitializeComponent();
        }

        private void button1_Click(object sender, EventArgs e)
        {
            Sender.SendData(Convert.ToString(friend) + Convert.ToString(textBox1.Text), Program._mut);
            textBox2.Text = textBox2.Text + "\r\n\r\n" + "sent a message on" + Convert.ToString(DateTime.Now) + textBox1.Text;
            textBox1.Text = null;
        }

        private void textBox1_TextChanged(object sender, EventArgs e)
        {
            if (textBox1.Text != null) button1.Enabled = true;
            else button1.Enabled = false;

        }

        private void Form1_FormClosed(object sender, FormClosedEventArgs e)
        {
            Sender.SendData("0", Program._mut);
        }

        private void Form1_Load(object sender, EventArgs e)
        {
           // this.Text = "Client" + Sender._id.ToString();
           Sender.ListChanged += this.ListBoxAssign;
           Sender.MessageCame += this.MessageShow;
        }

        private void ListBoxAssign(List<int> Clients)
        {
            listBox1.DataSource = Clients;
            listBox1.ValueMember = Clients.ToString();
            listBox1.DisplayMember = listBox1.ValueMember;
        }

        private void listBox1_SelectedIndexChanged(object sender, EventArgs e)
        {
            friend = Convert.ToInt32(listBox1.SelectedItem);
        }

        private void MessageShow(char[] message)
        {
            textBox2.Text = textBox2.Text + "\r\n\r\n" + "client " + message[1] + "sent you a message on "
                + Convert.ToString(DateTime.Now) + "\r\n" + message.ToString();
        }

       
    }
}
