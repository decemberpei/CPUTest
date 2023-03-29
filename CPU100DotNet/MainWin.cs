using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Threading;
using System.Threading.Tasks;
using System.Windows.Forms;
using System.Runtime.InteropServices;
using System.Diagnostics;

namespace CPU100DotNet
{
    public partial class MainWin : Form
    {
        private int mCoreCount = 1;
        private int mDuration = 1000;
        private static bool mDone = false;

        public MainWin()
        {
            InitializeComponent();
        }

        private void txt_core_count_TextChanged(object sender, EventArgs e)
        {
            try
            {
                mCoreCount = Int32.Parse(this.txt_core_count.Text);
                if (mCoreCount > Environment.ProcessorCount)
                {
                    mCoreCount = Environment.ProcessorCount;
                }
            }
            catch(Exception ex)
            {
                this.txt_core_count.Text = "" + mCoreCount;
            }
        }

        private void txt_duration_TextChanged(object sender, EventArgs e)
        {
            try
            {
                mDuration = Int32.Parse(this.txt_duration.Text);
            }
            catch (Exception ex)
            {
                this.txt_duration.Text = "" + mDuration;
            }
        }

        private void worker()
        {
            Console.WriteLine("worker start.");
            double i = 0.01f;
            while (true)
            {
                i++;
                i--;
                if (mDone)
                {
                    break;
                }
            }
            Console.WriteLine("worker done.");
        }

        private void checker()
        {
            Console.WriteLine("checker start.");
            DateTime startTime = DateTime.Now;
            while (true)
            {
                if(((TimeSpan)(DateTime.Now - startTime)).TotalMilliseconds > mDuration * 1000)
                {
                    mDone = true;
                    break;
                }
            }
            btn_run.Invoke((MethodInvoker)delegate {
                // Running on the UI thread
                btn_run.Enabled = mDone;
            });
            Console.WriteLine("checker done.");
            mDone = true;
        }

        private void btn_run_Click(object sender, EventArgs e)
        {
            mDone = false;
            Thread[] tw = new Thread[mCoreCount - 1];
            for (int i = 0; i< mCoreCount-1 ; i++)
            {
                tw[i] = new Thread(new ThreadStart(worker));
                tw[i].Start();
            }
            Thread tc = new Thread(new ThreadStart(checker));
            tc.Start();
            btn_run.Enabled = false;
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool AllocConsole();
        private void MainWin_Load(object sender, EventArgs e)
        {
            //AllocConsole();
            mCoreCount = Environment.ProcessorCount;
            this.txt_core_count.Text = "" + mCoreCount;
        }

        private void MainWin_FormClosing(object sender, System.Windows.Forms.FormClosingEventArgs e)
        {
            if (mDone == false)
            {
                mDone = true;
                Thread.Sleep(20);
            }
            Console.WriteLine("Application exiting.");
            Environment.Exit(0);
        }

        public enum PROCESS_INFORMATION_CLASS
        {
            ProcessMemoryPriority,
            ProcessMemoryExhaustionInfo,
            ProcessAppMemoryInfo,
            ProcessInPrivateInfo,
            ProcessPowerThrottling,
            ProcessReservedValue1,
            ProcessTelemetryCoverageInfo,
            ProcessProtectionLevelInfo,
            ProcessLeapSecondInfo,
            ProcessMachineTypeInfo,
            ProcessInformationClassMax
        }

        [StructLayout(LayoutKind.Sequential)]
        public struct PROCESS_POWER_THROTTLING_STATE
        {
            public int Version;
            public int ControlMask;
            public int StateMask;
        }

        [DllImport("kernel32.dll", SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        static extern bool SetProcessInformation(IntPtr hProcess, PROCESS_INFORMATION_CLASS processInformationClass, IntPtr processInformation, uint processInformationSize);

        private void set_qos(bool high)
        {
            var power_throtting_state = new PROCESS_POWER_THROTTLING_STATE { Version=1, ControlMask =1, StateMask = high ? 0 : 1 };
            var power_throtting_state_size = (uint)Marshal.SizeOf(power_throtting_state);
            var power_throtting_state_ptr = Marshal.AllocHGlobal((int)power_throtting_state_size);
            Marshal.StructureToPtr(power_throtting_state, power_throtting_state_ptr, false);

            if (!SetProcessInformation(Process.GetCurrentProcess().Handle, PROCESS_INFORMATION_CLASS.ProcessPowerThrottling, power_throtting_state_ptr, power_throtting_state_size))
            {
                throw new Win32Exception(Marshal.GetLastWin32Error());
            }
            else
            {
                Console.WriteLine("SetProcessInformation OK.");
            }
            Marshal.FreeHGlobal(power_throtting_state_ptr);
        }

        private void ck_box_qos_CheckedChanged(object sender, EventArgs e)
        {
            set_qos(ck_box_qos.Checked);
        }
    }
}
