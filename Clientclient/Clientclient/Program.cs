using System;
using System.Collections.Generic;
using System.Linq;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Text;
using System.Threading;
using System.Runtime.Serialization;
using System.Runtime.Serialization.Formatters.Binary;
using System.IO;

namespace Clientclient
{
    
    static class Program
    {
        /// <summary>
        /// The main entry point for the application.
        /// </summary>
        
        public static List<int> _clients;
        public static Mutex _mut = new Mutex();
        
    
        [STAThread]
        static void Main()
        {

            Thread mainThread = new Thread(() => Sender.CreateClient(_clients, _mut));
            mainThread.Start();
            Application.EnableVisualStyles();
            Application.SetCompatibleTextRenderingDefault(false);
            
            
          
        }
 
    }


    public class Sender
    {
       public delegate void ListChangedHandler(List<int> Clients);
       public static event ListChangedHandler ListChanged;

       public delegate void MessageCameHandler(char[] message);
       public static event MessageCameHandler MessageCame;
     
        public static Socket _clientSocket;

        
        private static Byte[] Buffer1 { get; set; }
        private static Byte[] Buffer2 { get; set; }
        public static int _id;
        public static char[] _message;
        internal static Thread thReceive;// принятие списка
        

        public static void CreateClient(List<int> clients, Mutex mut)
        {
            _clientSocket = new Socket(AddressFamily.InterNetwork, SocketType.Stream, ProtocolType.Tcp);
            _clientSocket.Blocking = true;
            IPEndPoint localEndPoint = new IPEndPoint(IPAddress.Loopback, 1234);
            
            while (true)
            {
                try
                {
                    _clientSocket.Connect(localEndPoint);
                    Application.Run(new Form1());
                    Sender.thReceive = new Thread(() => Sender.Receive(clients, mut));
                    thReceive.Start();
                }
                catch (Exception ex)
                {
                    Console.Write("Failed to connect :C");
                }
            }
            
        }


        protected static void OnMessageCame(char[] message)
        {
            if (MessageCame != null)
            {
                MessageCame(message);
            }
        }      


        protected static void OnListChanged(List<int> Clients)
        {
            if (ListChanged != null)
            {
                ListChanged(Clients);
            }
        }      

        internal static void SendData(string strData, Mutex mut)
        {
            Buffer1 = new Byte[sizeof(char) * (strData.Length)];
            Buffer1 = Encoding.ASCII.GetBytes(strData);
            mut.WaitOne();
            _clientSocket.Send(Buffer1);
            mut.ReleaseMutex();
            //throw new NotImplementedException();
        }

        internal static void Receive(List<int> clients, Mutex mut)
        {
            while (true)
            {
                Buffer2 = new Byte[_clientSocket.SendBufferSize];// 
                mut.WaitOne();
                _clientSocket.Receive(Buffer2);
                mut.ReleaseMutex();
                char[] message = Encoding.ASCII.GetChars(Buffer2);
                if (message[0] == 'm')
                {
                    _message = message;
                    OnMessageCame(_message);
                }
                else
                {
                    System.Runtime.Serialization.IFormatter formatter = new BinaryFormatter();
                    Stream stream = new MemoryStream(Buffer2);
                    //stream.Seek(0, SeekOrigin.Begin);
                    clients = (List<int>)formatter.Deserialize(stream);
                    OnListChanged(clients);
                }
            }
            //throw new NotImplementedException();

        }
        

    }

}
