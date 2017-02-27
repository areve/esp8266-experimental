import { Component, OnInit, Inject } from '@angular/core'

@Component({
  template: `
    <main class="serial-parallel-main">
      <h1>Serial Parallel</h1>
      <p>Control a serial-parallel chip from here</p>
      <p class="invalid">This page does not work, it may never...</p>
      <form>
        <ul>
          <li class="enabled"><label><input type="checkbox" name="enabled"> Enabled</label></li>
          <li class="latch">
            <label for="latch">
              Latch
            </label>
            <select [(ngModel)]="latchPin" name="latch" id="latch" aria-describedby="latch-error" [attr.aria-invalid]="!isLatchPinValid()">
              <option *ngFor="let o of pins" [value]="o">{{o}}</option>
            </select>
            <p class="help-text invalid" id="pin-error" [hidden]="isLatchPinValid()">latch pin must not be the same as other pins</p>
          </li>
          <li class="clock">
            <label for="clock">
              Clock
            </label>
            <select [(ngModel)]="clockPin" name="clock" id="clock" aria-describedby="clock-error" [attr.aria-invalid]="!isClockPinValid()">
              <option *ngFor="let o of pins" [value]="o">{{o}}</option>
            </select>
            <p class="help-text invalid" id="clock-error" [hidden]="isClockPinValid()">clock pin must not be the same as other pins</p>
          </li>
          <li class="data">
            <label for="data">
              Data
            </label>
            <select [(ngModel)]="dataPin" name="data" id="data" aria-describedby="data-error" [attr.aria-invalid]="!isDataPinValid()">
              <option *ngFor="let o of pins" [value]="o">{{o}}</option>
            </select>
            <p class="help-text invalid" id="data-error" [hidden]="isDataPinValid()">data pin must not be the same as other pins</p>
          </li>
          <li class="interval">
            <label for="interval">Interval <em>&micro;s</em></label>
            <input [(ngModel)]="interval" type="number" name="interval" id="interval" aria-describedby="data-error">
            <p class="help-text invalid" id="data-error" [hidden]="isIntervalInvalid()">invalid interval</p>
          </li>
        </ul>
        <button>Save</button>
      </form>
    </main>
  `
})

export class SerialParallelComponent {

  public latchPin: string = 'D5'
  public clockPin: string = 'D0'
  public dataPin: string = 'D6'
  public interval: number = 100000
  public pins: string[] = ['D0', 'D1', 'D2', 'D3', 'D4', 'D5', 'D6', 'D7', 'D8']

  isLatchPinValid () {
    return this.latchPin !== this.clockPin &&
      this.latchPin !== this.dataPin
  }

  isClockPinValid () {
    return this.clockPin !== this.latchPin &&
      this.clockPin !== this.dataPin
  }

  isDataPinValid () {
    return this.dataPin !== this.clockPin &&
      this.dataPin !== this.latchPin
  }

  isIntervalInvalid () {
    return true
  }
}
