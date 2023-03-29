
namespace CPU100DotNet
{
    partial class MainWin
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.components = new System.ComponentModel.Container();
            this.txt_core_count = new System.Windows.Forms.TextBox();
            this.txt_duration = new System.Windows.Forms.TextBox();
            this.contextMenuStrip1 = new System.Windows.Forms.ContextMenuStrip(this.components);
            this.textBox3 = new System.Windows.Forms.TextBox();
            this.textBox4 = new System.Windows.Forms.TextBox();
            this.btn_run = new System.Windows.Forms.Button();
            this.ck_box_qos = new System.Windows.Forms.CheckBox();
            this.SuspendLayout();
            // 
            // txt_core_count
            // 
            this.txt_core_count.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_core_count.Location = new System.Drawing.Point(235, 30);
            this.txt_core_count.Name = "txt_core_count";
            this.txt_core_count.Size = new System.Drawing.Size(137, 38);
            this.txt_core_count.TabIndex = 0;
            this.txt_core_count.Text = "1";
            this.txt_core_count.TextChanged += new System.EventHandler(this.txt_core_count_TextChanged);
            // 
            // txt_duration
            // 
            this.txt_duration.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.txt_duration.Location = new System.Drawing.Point(235, 93);
            this.txt_duration.Name = "txt_duration";
            this.txt_duration.Size = new System.Drawing.Size(137, 38);
            this.txt_duration.TabIndex = 1;
            this.txt_duration.Text = "1000";
            this.txt_duration.TextChanged += new System.EventHandler(this.txt_duration_TextChanged);
            // 
            // contextMenuStrip1
            // 
            this.contextMenuStrip1.ImageScalingSize = new System.Drawing.Size(32, 32);
            this.contextMenuStrip1.Name = "contextMenuStrip1";
            this.contextMenuStrip1.Size = new System.Drawing.Size(61, 4);
            // 
            // textBox3
            // 
            this.textBox3.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.textBox3.Enabled = false;
            this.textBox3.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox3.Location = new System.Drawing.Point(22, 24);
            this.textBox3.Name = "textBox3";
            this.textBox3.Size = new System.Drawing.Size(187, 44);
            this.textBox3.TabIndex = 3;
            this.textBox3.Text = "Core Count:";
            this.textBox3.WordWrap = false;
            // 
            // textBox4
            // 
            this.textBox4.BackColor = System.Drawing.SystemColors.ActiveBorder;
            this.textBox4.Enabled = false;
            this.textBox4.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.textBox4.Location = new System.Drawing.Point(22, 87);
            this.textBox4.Name = "textBox4";
            this.textBox4.Size = new System.Drawing.Size(187, 44);
            this.textBox4.TabIndex = 4;
            this.textBox4.Text = "Duration(s):";
            this.textBox4.WordWrap = false;
            // 
            // btn_run
            // 
            this.btn_run.Font = new System.Drawing.Font("Microsoft Sans Serif", 12F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.btn_run.Location = new System.Drawing.Point(22, 265);
            this.btn_run.Name = "btn_run";
            this.btn_run.Size = new System.Drawing.Size(187, 53);
            this.btn_run.TabIndex = 5;
            this.btn_run.Text = "Run";
            this.btn_run.UseVisualStyleBackColor = true;
            this.btn_run.Click += new System.EventHandler(this.btn_run_Click);
            // 
            // ck_box_qos
            // 
            this.ck_box_qos.AutoSize = true;
            this.ck_box_qos.Font = new System.Drawing.Font("Microsoft Sans Serif", 10.125F, System.Drawing.FontStyle.Regular, System.Drawing.GraphicsUnit.Point, ((byte)(0)));
            this.ck_box_qos.Location = new System.Drawing.Point(22, 194);
            this.ck_box_qos.Name = "ck_box_qos";
            this.ck_box_qos.Size = new System.Drawing.Size(156, 35);
            this.ck_box_qos.TabIndex = 6;
            this.ck_box_qos.Text = "HighQoS";
            this.ck_box_qos.UseVisualStyleBackColor = true;
            this.ck_box_qos.CheckedChanged += new System.EventHandler(this.ck_box_qos_CheckedChanged);
            // 
            // MainWin
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(12F, 25F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(524, 330);
            this.Controls.Add(this.ck_box_qos);
            this.Controls.Add(this.btn_run);
            this.Controls.Add(this.textBox4);
            this.Controls.Add(this.textBox3);
            this.Controls.Add(this.txt_duration);
            this.Controls.Add(this.txt_core_count);
            this.Name = "MainWin";
            this.Text = "CPU100";
            this.Load += new System.EventHandler(this.MainWin_Load);
            this.FormClosing += MainWin_FormClosing;
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.TextBox txt_core_count;
        private System.Windows.Forms.TextBox txt_duration;
        private System.Windows.Forms.ContextMenuStrip contextMenuStrip1;
        private System.Windows.Forms.TextBox textBox3;
        private System.Windows.Forms.TextBox textBox4;
        private System.Windows.Forms.Button btn_run;
        private System.Windows.Forms.CheckBox ck_box_qos;
    }
}

