import { Component, OnInit, Input } from '@angular/core';
import { Summary } from 'src/app/models/summary';
import { Solution } from 'src/app/models/solution';

@Component({
  selector: 'app-tile-list',
  templateUrl: './tile-list.component.html',
  styleUrls: ['./tile-list.component.scss']
})
export class TileListComponent implements OnInit {

  @Input()
  data: Summary[] | Solution [] = null;

  constructor() { }

  ngOnInit() {
  }

}
